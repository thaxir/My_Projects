#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hist-equ.h"

#define COLORS 256

__device__ int glb_hist[COLORS];


__global__ void calc_histogram(unsigned char * img_in, int offset_start, int offset_end){
     int ix = blockIdx.x * blockDim.x + threadIdx.x;;
    const int gridW = gridDim.x * blockDim.x;
    int Row, pos;

    __shared__ int hist[COLORS];

    if (threadIdx.x < COLORS) {
        hist[threadIdx.x] = 0;
    }
    __syncthreads();

    int RowNum = (offset_end - offset_start) / gridW;
    int extras = (offset_end - offset_start) % gridW;
    


    for (Row=0; Row<RowNum; Row++) {
        pos = Row * gridW + ix;
        atomicAdd(&hist[img_in[pos + offset_start]],1);
    }
    if (extras && ix < extras) {
        pos = Row * gridW + ix;
        atomicAdd(&hist[img_in[pos + offset_start]],1);
    }
    __syncthreads();
    if (threadIdx.x < COLORS) {
        atomicAdd(&glb_hist[threadIdx.x],hist[threadIdx.x]);
    }
}
 //int *lut = (int *)malloc(sizeof(int)*nbr_bin);
__global__ void calc_lut(int *lut, int img_size){ 

    
    __shared__ int shared_hist[COLORS];
    shared_hist[threadIdx.x] = glb_hist[threadIdx.x];
    __syncthreads();
    __shared__  int cdf[COLORS];
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
    int ix = blockIdx.x * blockDim.x + threadIdx.x;
    int iy = blockIdx.y * blockDim.y + threadIdx.y;
    const int gridW = gridDim.x * blockDim.x;
    int img_position1 = iy * gridW + ix; //thesh mesa sthn eikona synarthsh tou gridW 
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
