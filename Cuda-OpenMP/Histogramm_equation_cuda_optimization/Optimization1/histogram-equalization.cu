#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hist-equ.h"


__global__ void calc_histogram(int * hist_out, unsigned char * img_in, int img_size, int nbr_bin){
    
    int ix = blockIdx.x * blockDim.x + threadIdx.x;
    int iy = blockIdx.y * blockDim.y + threadIdx.y;
    const int gridW = gridDim.x * blockDim.x;
    int img_position = iy * gridW + ix; //thesh mesa sthn eikona synarthsh tou gridW 

   // __shared__ hist_out[nbr_bin];

    if (img_position < nbr_bin) { //allagh tou img_position me threadIdx.x se auto to if anevazei poly to contrast
        hist_out[img_position] = 0;
    }

    __syncthreads();

    if(img_position < img_size){
        atomicAdd(&hist_out[img_in[img_position]],1);
    }
    __syncthreads();
}
 //int *lut = (int *)malloc(sizeof(int)*nbr_bin);
__global__ void calc_lut(int *lut, int * hist_in, int img_size, int nbr_bin){ 

    
    __shared__ int shared_hist[256];
    shared_hist[threadIdx.x] = hist_in[threadIdx.x];
    __syncthreads();
    __shared__  int cdf[256];
    __syncthreads();

    int i, min, d; 
    //int cdf = 0;
    min = 0;
    i = 0;

    while(min == 0){
        min = shared_hist[i++];
    }
    d = img_size - min;
    for (unsigned int stride = 1; stride <= threadIdx.x; stride *= 2) {
        __syncthreads();
        shared_hist[threadIdx.x] += shared_hist[threadIdx.x-stride];
    }
    cdf[threadIdx.x] = shared_hist[threadIdx.x];
    //printf("cdf = %d\n",cdf);
    __syncthreads();
    
	

    //for(i = 0; i <= threadIdx.x; i ++){	//tha mporouse na ginei me prefix sum san veltistoipohsh FIXME
      //  cdf += shared_hist[i];
      //  lut[i] = (cdf - min)*(nbr_bin - 1)/d;        
    //}
    //printf("cdf = %d\n",cdf);
    

    lut[threadIdx.x] = (int)(((float)cdf[threadIdx.x] - min)*255/d + 0.5);
    if(lut[threadIdx.x] < 0){
        lut[threadIdx.x] = 0;
    }
}
__global__ void calc_output(unsigned char * img_out, unsigned char * img_in, int * lut, int img_size){
    /* Get the result image */
    int ix = blockIdx.x * blockDim.x + threadIdx.x;
    int iy = blockIdx.y * blockDim.y + threadIdx.y;
    const int gridW = gridDim.x * blockDim.x;
    int img_position1 = iy * gridW + ix; //thesh mesa sthn eikona synarthsh tou gridW 
    /* Construct the LUT by calculating the CDF */
    __syncthreads();
    if(img_position1 < img_size){
        if(lut[img_in[img_position1]] > 255){
            img_out[img_position1] = 255;
        }
        else{
            img_out[img_position1] = (unsigned char)lut[img_in[img_position1]];
        }
        
    }
}
