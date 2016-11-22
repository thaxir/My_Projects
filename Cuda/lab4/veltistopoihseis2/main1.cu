#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hist-equ.h"
#define STREAM_NUM 2

void run_cpu_gray_test(PGM_IMG img_in, char *out_filename);

int main(int argc, char *argv[]){
    PGM_IMG img_ibuf_g;

	if (argc != 3) {
		printf("Run with input file name and output file name as arguments\n");
		exit(1);
	}
	
    printf("Running contrast enhancement for gray-scale images.\n");
    img_ibuf_g = read_pgm(argv[1]);
    run_cpu_gray_test(img_ibuf_g, argv[2]);
    free_pgm(img_ibuf_g);

	return 0;
}



void run_cpu_gray_test(PGM_IMG img_in, char *out_filename)
{
    unsigned int timer = 0;
    PGM_IMG img_obuf;
    float gpu_time;
    cudaEvent_t start;
    cudaEvent_t stop;



    const int nstreams = STREAM_NUM;
    int img_Size = img_in.w * img_in.h;
    int streamSize = img_Size / nstreams;
    cudaStream_t *streams = (cudaStream_t*) malloc(nstreams * sizeof(cudaStream_t));
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    for(int i=0; i<nstreams; i++) {
        cudaStreamCreate(&(streams[i]));
    }

    printf("Starting GPU processing...\n");
    cudaEventRecord(start,0);

    //img_obuf = contrast_enhancement_g(img_in);
      PGM_IMG result, img_in_Gpu, result_in_Gpu;
    int * hist_in_Gpu, * dev_lut;
    int block_Dim, grid_Dimx, grid_Dimy;
 


    result.w = img_in.w;
    result.h = img_in.h;
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

    result.img = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));
    cudaMalloc((void **)&result_in_Gpu.img, result.w * result.h * sizeof(unsigned char));
    cudaMalloc((void **)&img_in_Gpu.img, result.w * result.h * sizeof(unsigned char));
    cudaMalloc((void **)&hist_in_Gpu, 256 * sizeof(int));
    cudaMalloc((void**)&dev_lut, 256 * sizeof(int));
    if ((result_in_Gpu.img == 0 )||(hist_in_Gpu == 0) || (img_in_Gpu.img == 0) || (dev_lut == 0)){
        printf("Failure in Gpu memory allocation\n");
        exit (0);
    }



    //cudaMemcpy(result_in_Gpu.img, result.img,  result.w * result.h * sizeof(unsigned char), cudaMemcpyHostToDevice);
    cudaMemcpy(img_in_Gpu.img, img_in.img,  result.w * result.h * sizeof(unsigned char), cudaMemcpyHostToDevice);
    for (int i=0; i<nstreams; i++) {
        int offset = i * streamSize;
        int offset1 = (i + 1) * streamSize;
        cudaMemcpyAsync(&result_in_Gpu.img[offset], &result.img[offset], streamSize * sizeof(unsigned char),
                                      cudaMemcpyHostToDevice, streams[i]);
        calc_histogram<<<256,256,0,streams[i]>>>(img_in_Gpu.img, offset, offset1);
    }


    cudaThreadSynchronize();
    cudaError_t error=cudaGetLastError();
    if(error!=cudaSuccess){
        printf("Cuda Error in calc_histogram:%s\n",cudaGetErrorString(error));
    }

    calc_lut<<<1,256>>>(dev_lut, result.w*result.h);

    cudaThreadSynchronize();
    cudaError_t error1=cudaGetLastError();
    if(error1!=cudaSuccess){
    printf("Cuda Error in calc_lut:%s\n",cudaGetErrorString(error1));
    }
    //for (int i=0; i<nstreams; i++) {
     //  int offset = i * streamSize;
     //   int offset1 = (i + 1) * streamSize;
      //  calc_output<<<256,256,0,streams[i]>>>(img_in_Gpu.img, offset, offset1);
    //}


    calc_output<<<dimGrid,dimBlock>>>(result_in_Gpu.img, img_in_Gpu.img, dev_lut, result.w*result.h);

    cudaThreadSynchronize();
    cudaError_t error2=cudaGetLastError();
    if(error2!=cudaSuccess){
        printf("Cuda Error in calc_output:%s\n",cudaGetErrorString(error2));
    }

    //for (int i=0; i<nstreams; i++) {
      //  int offset = i * streamSize;
      //  int offset1 = (i + 1) * streamSize;
      //  cudaMemcpyAsync(&result.img[offset], &result_in_Gpu.img[offset],streamSize * sizeof(unsigned char),cudaMemcpyDeviceToHost, streams[i]);
    //}





    cudaMemcpy(result.img, result_in_Gpu.img,  result.w * result.h * sizeof(unsigned char), cudaMemcpyDeviceToHost);
    img_obuf = result;




    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpu_time,start,stop);

    printf("GPU time used in seconds is %f\n", gpu_time );

    write_pgm(img_obuf, out_filename);
    free_pgm(img_obuf);
}


PGM_IMG read_pgm(const char * path){
    FILE * in_file;
    char sbuf[256];
    
    
    PGM_IMG result;
    int v_max;//, i;
    in_file = fopen(path, "r");
    if (in_file == NULL){
        printf("Input file not found!\n");
        exit(1);
    }
    
    fscanf(in_file, "%s", sbuf); /*Skip the magic number*/
    fscanf(in_file, "%d",&result.w);
    fscanf(in_file, "%d",&result.h);
    fscanf(in_file, "%d\n",&v_max);
    printf("Image size: %d x %d\n", result.w, result.h);
    

    result.img = (unsigned char *)malloc(result.w * result.h * sizeof(unsigned char));

        
    fread(result.img,sizeof(unsigned char), result.w*result.h, in_file);    
    fclose(in_file);
    
    return result;
}

void write_pgm(PGM_IMG img, const char * path){
    FILE * out_file;
    out_file = fopen(path, "wb");
    fprintf(out_file, "P5\n");
    fprintf(out_file, "%d %d\n255\n",img.w, img.h);
    fwrite(img.img,sizeof(unsigned char), img.w*img.h, out_file);
    fclose(out_file);
}

void free_pgm(PGM_IMG img)
{
    free(img.img);
}

