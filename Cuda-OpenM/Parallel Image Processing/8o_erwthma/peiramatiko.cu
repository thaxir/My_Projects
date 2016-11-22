/*
* This sample implements a separable convolution 
* of a 2D image with an arbitrary filter.
*/

#include <stdio.h>
#include <stdlib.h>

unsigned int filter_radius;

#define FILTER_LENGTH 	(2 * filter_radius + 1)
#define ABS(val)  	((val)<0.0 ? (-(val)) : (val))
#define accuracy  	0.00005 

 

////////////////////////////////////////////////////////////////////////////////
// Reference row convolution filter
////////////////////////////////////////////////////////////////////////////////
void convolutionRowCPU(float *h_Dst, float *h_Src, float *h_Filter, int imageW, int imageH, int filterR) {

  int x, y, k;
                      
  for (y = 0; y < imageH; y++) {
    for (x = 0; x < imageW; x++) {
      float sum = 0;

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
void convolutionColumnCPU(float *h_Dst, float *h_Src, float *h_Filter,
    			   int imageW, int imageH, int filterR) {

  int x, y, k;
  
  for (y = 0; y < imageH; y++) {
    for (x = 0; x < imageW; x++) {
      float sum = 0;

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

__global__ void convolutionRowGPU(float *h_Dst, float *h_Src, float *h_Filter, int imageW, int imageH, int filterR){

  int k,i,j;
  float sum = 0;
  int ix = blockIdx.x * blockDim.x + threadIdx.x;
  int iy = blockIdx.y * blockDim.y + threadIdx.y;

   for (i = 0; i < imageW ; i++){
    for(j = 0; j < imageW; j++){
      printf("%f ", h_Src[i * imageW + j]); //dn kserw an auto to printf eprepe na mou typwnei swsta apotelesmata episis ta stelnei sth Cpu kai meta sto strout h apo thn Gpu?? 
    }
    printf("\n"); 
  }
  for (k = -filterR; k <= filterR; k++) {
    int d = ix + k;    //edw einai to pou tha paei to filtro gi auto elegxei apo katw kai an to d einia ektos oriwn eikonas
    sum += h_Src[iy * imageH + d] * h_Filter[filterR - k];
    h_Dst[iy * imageW + ix] = sum;
    printf("%f", h_Dst[iy * imageW + ix]);
  }
}


__global__ void convolutionColumnGPU(float *h_Dst, float *h_Src, float *h_Filter, int imageW, int imageH, int filterR){
	int k;
	float sum = 0;
	int ix = blockIdx.x * blockDim.x + threadIdx.x;
	int iy = blockIdx.y * blockDim.y + threadIdx.y;
  for (k = -filterR; k <= filterR; k++) {
    int d = iy + k;
    sum += h_Src[d * imageW + ix] * h_Filter[filterR - k];
    h_Dst[iy * imageW + ix] = sum;
  }
}



////////////////////////////////////////////////////////////////////////////////
// Main program
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    
    float
    *h_Filter,
    *h_Input,
    *h_Buffer,
    *h_OutputCPU,
    *dev_Filter,
    *dev_Input,
    *dev_Buffer,
    *dev_OutputGPU,
    *dev_Padding,
    *h_apotelesmata,
    *h_Padding;


    int imageW;
    int imageH;
    int new_image_sizeH, new_image_sizeW;
    int block_Dim, grid_Dim;
    unsigned int i;
    unsigned int j;
    //FILE * fp;
    //fp = fopen("Max_accuracy.txt", "a");
    

    printf("Enter filter radius : ");
    scanf("%d", &filter_radius);
    //fprintf(fp,"for filter radius %d  ", filter_radius);

    // Ta imageW, imageH ta dinei o xrhsths kai thewroume oti einai isa,
    // dhladh imageW = imageH = N, opou to N to dinei o xrhsths.
    // Gia aplothta thewroume tetragwnikes eikones.  

    printf("Enter image size. Should be a power of two and greater than %d : ", FILTER_LENGTH);
    scanf("%d", &imageW);
    imageH = imageW;


    new_image_sizeW = imageW + 2 * filter_radius;   //to megethos tou padded  pinaka (h_Padding)
    new_image_sizeH = imageH + 2 * filter_radius;


    if (new_image_sizeW > 32){
      block_Dim = 32;
      grid_Dim = imageW / 32;
    }
    else{
      block_Dim = new_image_sizeW;
      grid_Dim = 1;
    }



    printf("Image Width x Height = %i x %i\n\n", imageW, imageH);
    printf("Allocating and initializing host arrays...\n");
    // Tha htan kalh idea na elegxete kai to apotelesma twn malloc...
    h_Padding = (float *)malloc(new_image_sizeW * new_image_sizeH * sizeof(float));
    h_Filter    = (float *)malloc(FILTER_LENGTH * sizeof(float));
    h_Input     = (float *)malloc(imageW * imageH * sizeof(float));
    h_Buffer    = (float *)malloc(imageW * imageH * sizeof(float));
    h_OutputCPU = (float *)malloc(imageW * imageH * sizeof(float));
    h_apotelesmata = (float *)malloc(imageW * imageH * sizeof(float)); //gia na epistrepsw to apotelesma apo thn GPU

    if ((h_Filter == 0 )||(h_Input == 0) || (h_Buffer == 0) || (h_OutputCPU == 0) || (h_Padding == 0)){
        printf("Failure in memory allocation\n");
        exit (0);
    }
    //Device allocation
    int size = imageW * imageH * sizeof(float);
    cudaMalloc((void**)&dev_Padding, new_image_sizeW * new_image_sizeH * sizeof(float));
    cudaMalloc((void**)&dev_Filter, FILTER_LENGTH * sizeof(float));
    cudaMalloc((void**)&dev_Input, size);
    cudaMalloc((void**)&dev_Buffer, new_image_sizeW * new_image_sizeH * sizeof(float));//allazei kai to size tou buffer afou to prwto convolution apothikeuei to apotelesma edw 
    cudaMalloc((void**)&dev_OutputGPU, size);

    if ((dev_Filter == 0 )||(dev_Input == 0) || (dev_Buffer == 0) || (dev_OutputGPU == 0) || (dev_Padding == 0)){
        printf("Failure in Gpu memory allocation\n");
        exit (0);
    }

    //arxikopoihsh gia kathe endexomeno
    cudaMemset(dev_Padding, 0 , new_image_sizeW * new_image_sizeH * sizeof(float));
    cudaMemset(dev_Filter, 0 , FILTER_LENGTH * sizeof(float));
    cudaMemset(dev_Input, 0, size);
    cudaMemset(dev_Buffer, 0, new_image_sizeW * new_image_sizeH * sizeof(float));
    cudaMemset(dev_OutputGPU, 0, size);

    // to 'h_Filter' apotelei to filtro me to opoio ginetai to convolution kai
    // arxikopoieitai tuxaia. To 'h_Input' einai h eikona panw sthn opoia ginetai
    // to convolution kai arxikopoieitai kai auth tuxaia.

    srand(200);

    for (i = 0; i < FILTER_LENGTH; i++) {
        h_Filter[i] = (float)(rand() % 16);
    }

    for (i = 0; i < imageW * imageH; i++) {
        h_Input[i] = (float)rand() / ((float)RAND_MAX / 255) + (float)rand() / (float)RAND_MAX;
    }
    //for (i = 0; i < imageW ; i++){
      //for(j = 0; j < imageH; j++){
       // printf("%f ",h_Input[i * imageH + j]); 
      //}
     // printf("\n"); 
    //}
    
    //Mhdenizw ton padded pinaka  
    for (i = 0; i < new_image_sizeW; i++){
      for (j = 0; j< new_image_sizeH; j++){
        h_Padding[i * new_image_sizeW + j] = 0;
      }
    }

    //Enopoiw tous 2 pinakes wste na ftiaxtei o telikos padded pinakas
    for (i = 0; i < imageW; i++){
      for (j = 0; j < imageH; j++){
        h_Padding[(i + filter_radius) * new_image_sizeW + (j+filter_radius)] = h_Input[i * imageH + j];

      }
    }


    for (i = 0; i < new_image_sizeW ; i++){
      for(j = 0; j < new_image_sizeH; j++){
        printf("%f ",h_Padding[i * new_image_sizeH + j]); 
      }
      printf("\n"); 
    }

    //memcpy afou gemisoun oi pinakes(eikones)
    cudaMemcpy(dev_Filter, h_Filter, FILTER_LENGTH * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_Padding, h_Padding, new_image_sizeW * new_image_sizeH * sizeof(float), cudaMemcpyHostToDevice);

    dim3 dimGrid(grid_Dim, grid_Dim);
    dim3 dimBlock(block_Dim, block_Dim);
    // To parakatw einai to kommati pou ekteleitai sthn CPU kai me vash auto prepei na ginei h sugrish me thn GPU.
    printf("CPU computation...\n");

    convolutionRowCPU(h_Buffer, h_Input, h_Filter, imageW, imageH, filter_radius); // convolution kata grammes
    convolutionColumnCPU(h_OutputCPU, h_Buffer, h_Filter, imageW, imageH, filter_radius); // convolution kata sthles

    for (i = 0; i < imageW * imageH; i++) {    // stamataw tis ektypwseis gt dn pairnei apeiro xrono mexri na tis deiksei oles
      printf("%f\n",h_OutputCPU[i]);
    }

    // Kanete h sugrish anamesa se GPU kai CPU kai an estw kai kapoio apotelesma xeperna thn akriveia
    // pou exoume orisei, tote exoume sfalma kai mporoume endexomenws na termatisoume to programma mas 

    printf("GPU computation...\n");
    convolutionRowGPU<<<dimGrid, dimBlock>>>(dev_Buffer, dev_Padding, dev_Filter, new_image_sizeW, imageW, filter_radius);

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

    for (i = 0; i < imageW * imageH; i++) {
      printf("%f\n",h_apotelesmata[i]);
    }
    

    float diafora = 0;
    float Max_acc = -1;
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
           
    if(Max_acc > accuracy){
    	printf("CPU and GPU results don't match and program is gonna terminate\n");
      	exit(0);
    }
    // free all the allocated memory
    free(h_OutputCPU);
    free(h_Buffer);
    free(h_Input);
    free(h_Filter);
    free(h_Padding);
    free(h_apotelesmata);
    cudaFree(dev_Padding);
    cudaFree(dev_Filter);
    cudaFree(dev_Input);
    cudaFree(dev_Buffer);
    cudaFree(dev_OutputGPU);

    // Do a device reset just in case... Bgalte to sxolio otan ylopoihsete CUDA
    cudaDeviceReset();


    return 0;
}

