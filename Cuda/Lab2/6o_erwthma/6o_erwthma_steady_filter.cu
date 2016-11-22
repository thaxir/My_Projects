/*
* This sample implements a separable convolution 
* of a 2D image with an arbitrary filter.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int filter_radius;

#define FILTER_LENGTH 	(2 * filter_radius + 1)
#define ABS(val)  	((val)<0.0 ? (-(val)) : (val))
#define accuracy  	0.00005 

 

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
    *dev_OutputGPU,
    *h_apotelesmata;

    clock_t start, startGPU, endGPU, end;
    double cpu_time_used,gpu_time_used;


    int imageW;
    int imageH;
    int block_Dim, grid_Dim;
    unsigned int i;
    FILE * fp;
    FILE * fp1;

    fp = fopen("Xronoi_Ekteleshs_CPU_double_steady_filter.txt", "a");
    fp1 = fopen("Xronoi_Ekteleshs_GPU_double_steady_filter.txt", "a");
    

    //printf("Enter filter radius : ");
    //scanf("%d", &filter_radius);
    //fprintf(fp,"%d\n", filter_radius);
    //fprintf(fp1,"%d\n", filter_radius);
    filter_radius = 16;
    printf("filter radius is %d\n", filter_radius);

    // Ta imageW, imageH ta dinei o xrhsths kai thewroume oti einai isa,
    // dhladh imageW = imageH = N, opou to N to dinei o xrhsths.
    // Gia aplothta thewroume tetragwnikes eikones.  

    printf("Enter image size. Should be a power of two and greater than %d : ", FILTER_LENGTH);
    scanf("%d", &imageW);
    imageH = imageW;

    if (imageW > 32){
      block_Dim = 32;
      grid_Dim = imageW / 32;
    }
    else{
      block_Dim = imageW;
      grid_Dim = 1;
    }

    printf("Image Width x Height = %i x %i\n\n", imageW, imageH);
    fprintf(fp,"%d * %d\n", imageW, imageH);
    fprintf(fp1,"%d * %d\n", imageW, imageH);

    printf("Allocating and initializing host arrays...\n");
    // Tha htan kalh idea na elegxete kai to apotelesma twn malloc...
    h_Filter    = (double *)malloc(FILTER_LENGTH * sizeof(double));
    h_Input     = (double *)malloc(imageW * imageH * sizeof(double));
    h_Buffer    = (double *)malloc(imageW * imageH * sizeof(double));
    h_OutputCPU = (double *)malloc(imageW * imageH * sizeof(double));
    h_apotelesmata = (double *)malloc(imageW * imageH * sizeof(double)); //gia na epistrepsw to apotelesma apo thn GPU

    if ((h_Filter == 0 )||(h_Input == 0) || (h_Buffer == 0) || (h_OutputCPU == 0)){
        printf("Failure in memory allocation\n");
        exit (0);
    }
    //Device allocation
    int size = imageW * imageH * sizeof(double);
    cudaMalloc((void**)&dev_Filter, FILTER_LENGTH * sizeof(double));
    cudaMalloc((void**)&dev_Input, size);
    cudaMalloc((void**)&dev_Buffer, size);
    cudaMalloc((void**)&dev_OutputGPU, size);

    if ((dev_Filter == 0 )||(dev_Input == 0) || (dev_Buffer == 0) || (dev_OutputGPU == 0)){
        printf("Failure in Gpu memory allocation\n");
        exit (0);
    }

    //arxikopoihsh gia kathe endexomeno
    cudaMemset(dev_Filter, 0 , FILTER_LENGTH * sizeof(double));
    cudaMemset(dev_Input, 0, size);
    cudaMemset(dev_Buffer, 0, size);
    cudaMemset(dev_OutputGPU, 0, size);

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

    printf("CPU computation...\n");

    start = clock();
    convolutionRowCPU(h_Buffer, h_Input, h_Filter, imageW, imageH, filter_radius); // convolution kata grammes
    convolutionColumnCPU(h_OutputCPU, h_Buffer, h_Filter, imageW, imageH, filter_radius); // convolution kata sthles
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //for (i = 0; i < imageW * imageH; i++) {    // stamataw tis ektypwseis gt dn pairnei apeiro xrono mexri na tis deiksei oles
     //  printf("%f\n",h_OutputCPU[i]);
    //}
    
    //memcpy afou gemisoun oi pinakes(eikones)
    

    startGPU = clock();
    cudaMemcpy(dev_Filter, h_Filter, FILTER_LENGTH * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_Input, h_Input, size, cudaMemcpyHostToDevice);

    dim3 dimGrid(grid_Dim, grid_Dim);
    dim3 dimBlock(block_Dim, block_Dim);

    // Kanete h sugrish anamesa se GPU kai CPU kai an estw kai kapoio apotelesma xeperna thn akriveia
    // pou exoume orisei, tote exoume sfalma kai mporoume endexomenws na termatisoume to programma mas 

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
    
    cudaMemcpy(h_apotelesmata, dev_OutputGPU , size, cudaMemcpyDeviceToHost);

    endGPU = clock();

    gpu_time_used = ((double) (endGPU - startGPU)) / CLOCKS_PER_SEC;
    
    //for (i = 0; i < imageW * imageH; i++) {
    //  printf("%f\n",h_apotelesmata[i]);
    //}
    

    double diafora = 0;
    double Max_acc = -1;
  	for (i = 0; i < imageW * imageH; i++) {
      diafora = h_OutputCPU[i] - h_apotelesmata[i];
      diafora = ABS(diafora);
      if (diafora > Max_acc){
      	Max_acc = diafora;
      }
    }
    printf ("to grid einia %d kai to block einia %d\n", grid_Dim, block_Dim);
    printf ("The Max_accuracy is %f\n", Max_acc);
    //fprintf(fp,"the Max accuracy is    %32f\n",Max_acc);
    printf("CPU time used in seconds is %f\n", cpu_time_used);
    fprintf(fp,"%f\n", cpu_time_used);
    fprintf(fp1,"%f\n", gpu_time_used);
    printf("GPU time used in seconds is %f\n", gpu_time_used);
    
    if(Max_acc > accuracy){
    	printf("CPU and GPU results don't match and program is gonna terminate\n");
      	exit(0);
    }

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

