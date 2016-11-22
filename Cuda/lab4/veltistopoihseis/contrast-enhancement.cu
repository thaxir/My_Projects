#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hist-equ.h"

PGM_IMG contrast_enhancement_g(PGM_IMG img_in)
{
    PGM_IMG result, img_in_Gpu, result_in_Gpu;
    int * hist_in_Gpu, * dev_lut;
    int block_Dim, grid_Dimx, grid_Dimy;


    result.w = img_in.w;
    result.h = img_in.h;
	

    result.img = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));
    cudaMalloc((void **)&result_in_Gpu.img, result.w * result.h * sizeof(unsigned char));
    cudaMalloc((void **)&img_in_Gpu.img, result.w * result.h * sizeof(unsigned char));
    cudaMalloc((void **)&hist_in_Gpu, 256 * sizeof(int));
    cudaMalloc((void**)&dev_lut, 256 * sizeof(int));
    if ((result_in_Gpu.img == 0 )||(hist_in_Gpu == 0) || (img_in_Gpu.img == 0) || (dev_lut == 0)){
        printf("Failure in Gpu memory allocation\n");
        exit (0);
    }



    cudaMemcpy(result_in_Gpu.img, result.img,  result.w * result.h * sizeof(unsigned char), cudaMemcpyHostToDevice);
	cudaMemcpy(img_in_Gpu.img, img_in.img,  result.w * result.h * sizeof(unsigned char), cudaMemcpyHostToDevice);



    if(result.w > 32){     
        block_Dim = 32;
         grid_Dimx = (result.w / 32) + 1;
         grid_Dimy = (result.w / 32) + 1;
    }
    else{
        block_Dim = result.w;
        grid_Dimx = 1;
        grid_Dimy = 1;
    }
    
    dim3 dimBlock(block_Dim,block_Dim);
    dim3 dimGrid(grid_Dimx,grid_Dimy);

    calc_histogram<<<dimGrid,dimBlock>>>(hist_in_Gpu, img_in_Gpu.img,  result.w*result.h, 256);

    cudaThreadSynchronize();
    cudaError_t error=cudaGetLastError();
    if(error!=cudaSuccess){
        printf("Cuda Error in calc_histogram:%s\n",cudaGetErrorString(error));
    }

    calc_lut<<<1,256>>>(dev_lut, hist_in_Gpu, result.w*result.h, 256);

    cudaThreadSynchronize();
    cudaError_t error1=cudaGetLastError();
    if(error1!=cudaSuccess){
    printf("Cuda Error in calc_lut:%s\n",cudaGetErrorString(error1));
    }

    calc_output<<<dimGrid,dimBlock>>>(result_in_Gpu.img, img_in_Gpu.img, dev_lut, result.w*result.h);

    cudaThreadSynchronize();
    cudaError_t error2=cudaGetLastError();
    if(error2!=cudaSuccess){
        printf("Cuda Error in calc_output:%s\n",cudaGetErrorString(error2));
    }

    cudaMemcpy(result.img, result_in_Gpu.img,  result.w * result.h * sizeof(unsigned char), cudaMemcpyDeviceToHost);
    return result;
}



















