/*
* This sample implements a separable convolution 
* of a 2D image with an arbitrary filter.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int filter_radius ;

#define FILTER_LENGTH 	(2 * 16 + 1)
#define ABS(val)  	((val)<0.0 ? (-(val)) : (val))
#define accuracy  	0.00005 
#define TILE_WIDTH  32

 __constant__ double Filter_in_constant_mem[FILTER_LENGTH];  //pernaw to filtro sthn constant memory gt auto mono tha diavazetai

////////////////////////////////////////////////////////////////////////////////
// Reference row convolution filter
////////////////////////////////////////////////////////////////////////////////
void convolutionRowCPU(double *h_Dst, double *h_Src, double *h_Filter, 
                       int imageW, int imageH, int filterR) {

  int x, y, k;
                      
  for (y = 0; y < imageH; y++) {
    for (x = 0; x < imageW; x++) {
      double sum = 0;

      for (k = -filterR; k <= filterR; k++) {
        int d = x + k;		//edw einai to pou tha paei to filtro gi auto elegxei apo katw kai an to d einia ektos oriwn eikonas

        if (d >= 0 && d < imageW) {
          sum += h_Src[y * imageW + d] * h_Filter[filterR - k];
        }     

        h_Dst[y * imageW + x] = sum;
      }
    }
  }
        
}


////////////////////////////////////////////////////////////////////////////////
// Reference column convolution filter
////////////////////////////////////////////////////////////////////////////////
void convolutionColumnCPU(double *h_Dst, double *h_Src, double *h_Filter,
    			   int imageW, int imageH, int filterR) {

  int x, y, k;
  
  for (y = 0; y < imageH; y++) {
    for (x = 0; x < imageW; x++) {
      double sum = 0;

      for (k = -filterR; k <= filterR; k++) {
        int d = y + k;

        if (d >= 0 && d < imageH) {
          sum += h_Src[d * imageW + x] * h_Filter[filterR - k];
        }   
 
        h_Dst[y * imageW + x] = sum;
      }
    }
  }
    
}

__global__ void convolutionRowGPU(double *h_Dst, double *h_Src, double *h_Filter, int imageW, int imageH, int filterR){

  int k;
  double sum = 0;
  int ix = blockIdx.x * blockDim.x + threadIdx.x;
  int iy = blockIdx.y * blockDim.y + threadIdx.y;
  for (k = -filterR; k <= filterR; k++) {
    int d = ix + k;    //edw einai to pou tha paei to filtro gi auto elegxei apo katw kai an to d einia ektos oriwn eikonas
    if (d >= 0 && d < imageW) {
      sum += h_Src[iy * imageW + d] * h_Filter[filterR - k];
    }
    h_Dst[iy * imageW + ix] = sum;
  }
}


__global__ void convolutionColumnGPU(double *h_Dst, double *h_Src, double *h_Filter, int imageW, int imageH, int filterR){
	int k;
	double sum = 0;
	int ix = blockIdx.x * blockDim.x + threadIdx.x;
	int iy = blockIdx.y * blockDim.y + threadIdx.y;
  for (k = -filterR; k <= filterR; k++) {
    int d = iy + k;
    if (d >= 0 && d < imageH) {
      sum += h_Src[d * imageW + ix] * h_Filter[filterR - k];
    }
    h_Dst[iy * imageW + ix] = sum;
  }
}



__global__ void convolutionTileRowGPU(double *h_Dst, double *h_Src, int imageW, int imageH, int filterR){


  __shared__ double tiled_Src[TILE_WIDTH][TILE_WIDTH];

  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;
  int k;

  int ix = blockIdx.x * blockDim.x + threadIdx.x;
  int iy = blockIdx.y * blockDim.y + threadIdx.y;

  int Row = by * TILE_WIDTH + ty;
  int Col = bx * TILE_WIDTH + tx;

  tiled_Src[ty][tx] = h_Src[Row * imageW + (bx * TILE_WIDTH + tx)];
  __syncthreads(); //ola ta nhmata tou block exoun oloklhrwsei thn fortwsh ston tiled_Src

  double sum = 0;

  for (k = -filterR; k <= filterR; k++) {
    int d = tx + k;  

    if (d >= 0 && d < TILE_WIDTH ) {
      sum += tiled_Src[ty][d] * Filter_in_constant_mem[filterR - k];
    }
    else if((ix + k > 0) && (ix + k < imageW)){
      sum += h_Src[iy * imageW + (ix + k)] * Filter_in_constant_mem[filterR - k];
    }
    __syncthreads(); //gia na eksasfalisei oti ta nhmata tou block exoun teliwsei me ton tiled_Src

    h_Dst[Row * imageW + Col] = sum;
    __syncthreads();
  }
  __syncthreads();
}



__global__ void convolutionTileColumnGPU(double *h_Dst, double *h_Src, int imageW, int imageH, int filterR){


  __shared__ double tiled_Src[TILE_WIDTH][TILE_WIDTH];

  int bx = blockIdx.x;
  int by = blockIdx.y;
  int tx = threadIdx.x;
  int ty = threadIdx.y;
  int k;

  int ix = blockIdx.x * blockDim.x + threadIdx.x;
  int iy = blockIdx.y * blockDim.y + threadIdx.y;

  int Row = by * TILE_WIDTH + ty;
  int Col = bx * TILE_WIDTH + tx;

  tiled_Src[ty][tx] = h_Src[(by * TILE_WIDTH + ty) * imageW + Col];
  __syncthreads(); //ola ta nhmata tou block exoun oloklhrwsei thn fortwsh ston tiled_Src

  double sum = 0;

  for (k = -filterR; k <= filterR; k++) {
    int d = ty + k;  

    if (d >= 0 && d < TILE_WIDTH ) {
      sum += tiled_Src[d][tx] * Filter_in_constant_mem[filterR - k];
    }
    else if((iy + k > 0) && (iy + k < imageW)){
      sum += h_Src[(iy + k) * imageW + ix] * Filter_in_constant_mem[filterR - k];
    }
    __syncthreads(); //gia na eksasfalisei oti ta nhmata tou block exoun teliwsei me ton tiled_Src
    h_Dst[Row * imageW + Col] = sum;
    __syncthreads();
  }

__syncthreads();
}



////////////////////////////////////////////////////////////////////////////////
// Main program
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    
    double
    *h_Filter,
    *h_Input,
    *h_Buffer,
    *h_OutputCPU,
    *dev_Filter,
    *dev_Input,
    *dev_Buffer,
    *dev_new_Buffer,
    *dev_OutputGPU,
    *dev_new_OutputGPU,
    *h_apotelesmata,
    *h_apotelesmata2;

    //clock_t startCPU, startGPU, endGPU, endCPU;
    double cpu_time_used;

    float gpu_time_used_no_tile, gpu_time_used;

    cudaEvent_t start, stop, start1, stop1;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventCreate(&start1);
    cudaEventCreate(&stop1);


    int imageW;
    int imageH;
    int block_Dim, grid_Dim;
    unsigned int i;
    FILE * fp;
    fp = fopen("Xronoi_Ekteleshs_GPU_tiled_DOUBLE.txt", "a");
    

    //printf("Enter filter radius : ");
    //scanf("%d", &filter_radius);
    filter_radius = 16;
    //fprintf(fp,"for filter radius %d  ", filter_radius);

    // Ta imageW, imageH ta dinei o xrhsths kai thewroume oti einai isa,
    // dhladh imageW = imageH = N, opou to N to dinei o xrhsths.
    // Gia aplothta thewroume tetragwnikes eikones.  

    printf("Enter image size. Should be a power of two and greater than %d : ", FILTER_LENGTH);
    scanf("%d", &imageW);
    imageH = imageW;
    fprintf(fp, "%d x %d", imageW, imageW);

    if (imageW > 32){
      block_Dim = 32;
      grid_Dim = imageW / block_Dim;
    }
    else{
      block_Dim = imageW;
      grid_Dim = 1;
    }

    printf("Image Width x Height = %i x %i\n\n", imageW, imageH);
    printf("Allocating and initializing host arrays...\n");
    // Tha htan kalh idea na elegxete kai to apotelesma twn malloc...
    h_Filter    = (double *)malloc(FILTER_LENGTH * sizeof(double));
    h_Input     = (double *)malloc(imageW * imageH * sizeof(double));
    h_Buffer    = (double *)malloc(imageW * imageH * sizeof(double));
    h_OutputCPU = (double *)malloc(imageW * imageH * sizeof(double));
    h_apotelesmata = (double *)malloc(imageW * imageH * sizeof(double)); //gia na epistrepsw to apotelesma apo thn GPU
    h_apotelesmata2= (double *)malloc(imageW * imageH * sizeof(double));  //gia na epistrepsw ta apotelemsata apo thn GPU gia to tiled convolution

    if ((h_Filter == 0 )||(h_Input == 0) || (h_Buffer == 0) || (h_OutputCPU == 0) || (h_apotelesmata2 == 0) || (h_apotelesmata == 0)){
        printf("Failure in memory allocation\n");
        exit (0);
    }
    //Device allocation
    int size = imageW * imageH * sizeof(double);
    cudaMalloc((void**)&dev_Filter, FILTER_LENGTH * sizeof(double));
    cudaMalloc((void**)&dev_Input, size);
    cudaMalloc((void**)&dev_Buffer, size);
    cudaMalloc((void**)&dev_new_Buffer, size);  //gia tis nees synarthseis pou tha dhmiourghsw
    cudaMalloc((void**)&dev_OutputGPU, size);   
    cudaMalloc((void**)&dev_new_OutputGPU, size); //gia tis nees synarthseis pou tha dhmiourghsw

    if ((dev_Filter == 0 )||(dev_Input == 0) || (dev_Buffer == 0) || (dev_OutputGPU == 0) || (dev_new_Buffer == 0) || (dev_new_OutputGPU == 0)){
        printf("Failure in Gpu memory allocation\n");
        exit (0);
    }

    //arxikopoihsh gia kathe endexomeno
    cudaMemset(dev_Filter, 0 , FILTER_LENGTH * sizeof(double));
    cudaMemset(dev_Input, 0, size);
    cudaMemset(dev_Buffer, 0, size);
    cudaMemset(dev_OutputGPU, 0, size);
    cudaMemset(dev_new_OutputGPU, 0, size);
    cudaMemset(dev_new_Buffer, 0, size);

    // to 'h_Filter' apotelei to filtro me to opoio ginetai to convolution kai
    // arxikopoieitai tuxaia. To 'h_Input' einai h eikona panw sthn opoia ginetai
    // to convolution kai arxikopoieitai kai auth tuxaia.

    srand(200);

    for (i = 0; i < FILTER_LENGTH; i++) {
        h_Filter[i] = (double)(rand() % 16);
    }

    for (i = 0; i < imageW * imageH; i++) {
        h_Input[i] = (double)rand() / ((double)RAND_MAX / 255) + (double)rand() / (double)RAND_MAX;
    }
    // To parakatw einai to kommati pou ekteleitai sthn CPU kai me vash auto prepei na ginei h sugrish me thn GPU.

    //printf("CPU computation...\n");

    //start = clock();
    //convolutionRowCPU(h_Buffer, h_Input, h_Filter, imageW, imageH, filter_radius); // convolution kata grammes
    //convolutionColumnCPU(h_OutputCPU, h_Buffer, h_Filter, imageW, imageH, filter_radius); // convolution kata sthles
    //end = clock();
    //cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //for (i = 0; i < imageW * imageH; i++) {    // stamataw tis ektypwseis gt dn pairnei apeiro xrono mexri na tis deiksei oles
     //  printf("%f\n",h_OutputCPU[i]);
    //}
    
    //memcpy afou gemisoun oi pinakes(eikones)
    

    
    cudaMemcpy(dev_Filter, h_Filter, FILTER_LENGTH * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_Input, h_Input, size, cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(Filter_in_constant_mem,h_Filter,FILTER_LENGTH * sizeof(double));  //pernaw to Filtro sthn constant memory

    dim3 dimGrid(grid_Dim, grid_Dim);
    dim3 dimBlock(block_Dim, block_Dim);

    // Kanete h sugrish anamesa se GPU kai CPU kai an estw kai kapoio apotelesma xeperna thn akriveia
    // pou exoume orisei, tote exoume sfalma kai mporoume endexomenws na termatisoume to programma mas 

    //startGPU = clock();
    cudaEventRecord(start, 0);
    printf("GPU computation...\n");
    convolutionRowGPU<<<dimGrid, dimBlock>>>(dev_Buffer, dev_Input, dev_Filter, imageW, imageH, filter_radius);

    // check for error dn vgainei gia na dw gt xtypaei to 2o error 
    cudaError_t error = cudaGetLastError();
    if(error != cudaSuccess){
      // print the CUDA error message and exit
      printf("CUDA error: %s\n", cudaGetErrorString(error));
    }
    
    convolutionColumnGPU<<<dimGrid, dimBlock>>>(dev_OutputGPU, dev_Buffer, dev_Filter, imageW, imageH, filter_radius);

    // check for error
    cudaError_t error1 = cudaGetLastError();
    if(error1 != cudaSuccess){
      // print the CUDA error message and exit
      printf("CUDA error: %s\n", cudaGetErrorString(error1));
    }
    
    //endGPU = clock();
    cudaEventRecord(stop, 0); 
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time_used_no_tile,start,stop);

    cudaMemcpy(h_apotelesmata, dev_OutputGPU , size, cudaMemcpyDeviceToHost);


    //gpu_time_used = ((double) (endGPU - startGPU)) / CLOCKS_PER_SEC;
    
    //for (i = 0; i < imageW * imageH; i++) {
      //printf("%f\n",h_apotelesmata[i]);
    //}
    

    //double diafora = 0;
    //double Max_acc = -1;
  	//for (i = 0; i < imageW * imageH; i++) {
     // diafora = h_OutputCPU[i] - h_apotelesmata[i];
     // diafora = ABS(diafora);
     // if (diafora > Max_acc){
      //	Max_acc = diafora;
      //}
    //}

    dim3 new_block(block_Dim,block_Dim);
    dim3 new_grid(imageW/block_Dim,imageH/block_Dim);

    cudaEventRecord(start1, 0);

    convolutionTileRowGPU<<<new_grid, new_block>>>(dev_new_Buffer, dev_Input, imageW, imageH, filter_radius);
    convolutionTileColumnGPU<<<new_grid, new_block>>>(dev_new_OutputGPU, dev_new_Buffer, imageW, imageH, filter_radius);

    cudaEventRecord(stop1, 0); 
    cudaEventSynchronize(stop1);
    cudaEventElapsedTime(&gpu_time_used,start1,stop1);

    cudaMemcpy(h_apotelesmata2, dev_new_OutputGPU , size, cudaMemcpyDeviceToHost);

    int thesh = 0;
    double diafora = 0;
    double Max_acc = -1;
    for (i = 0; i < imageW * imageH; i++) {
      diafora = h_apotelesmata[i] - h_apotelesmata2[i];
      diafora = ABS(diafora);
      //printf("h_apotelesmata = %f kai h_apotelesmata2 = %f\n", h_apotelesmata[i], h_apotelesmata2[i]);
      if (diafora > Max_acc){
        Max_acc = diafora;
        thesh = i;
      }
    }

    printf ("H Megisth diafora metaksi tou tiledConvolution kai tou aplou einai %f kai einia sth thesh %d \n", Max_acc, thesh);


    printf ("to grid einia %d kai to block einia %d\n", grid_Dim, block_Dim);
    //printf ("The Max_accuracy is %f\n", Max_acc);
    //fprintf(fp,"the Max accuracy is    %32f\n",Max_acc);
    //printf("CPU time used in seconds is %f\n", cpu_time_used);
    printf("GPU time used in seconds is %f\n", gpu_time_used);
    fprintf(fp, "    %f\n", gpu_time_used);
    
    //if(Max_acc > accuracy){
    	//printf("CPU and GPU results don't match and program is gonna terminate\n");
      //	exit(0);
    //}

    // free all the allocated memory
    free(h_OutputCPU);
    free(h_Buffer);
    free(h_Input);
    free(h_Filter);
    free(h_apotelesmata);
    cudaFree(dev_Filter);
    cudaFree(dev_Input);
    cudaFree(dev_Buffer);
    cudaFree(dev_OutputGPU);

    // Do a device reset just in case... Bgalte to sxolio otan ylopoihsete CUDA
    cudaDeviceReset();


    return 0;
}

