#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

__global__ void add(int* d_vec1, int* d_vec2, int* d_vec3)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	d_vec3[idx] = d_vec2[idx] + d_vec1[idx];
}

int main()
{
	int i ;

	int num_blocks = 1000;
	int num_threads = 512;

	int SIZE = num_threads*num_blocks;
	int BYTES = SIZE * sizeof(int);

	// declare device and host variables
	int h_vec1[SIZE],h_vec2[SIZE],h_vec3[SIZE];
	int *d_vec1, *d_vec2, *d_vec3;

	// allocate memory on the device
	cudaMalloc((void**)&d_vec1,BYTES);
	cudaMalloc((void**)&d_vec2,BYTES);
	cudaMalloc((void**)&d_vec3,BYTES);

	// generate array on host
	for(i=0;i<SIZE;i++)
	{
		h_vec1[i] = rand()%20;
		h_vec2[i] = rand()%20;
		h_vec3[i] = 0;
	}

	// move variables from host to device
	cudaMemcpy(d_vec1,h_vec1,BYTES,cudaMemcpyHostToDevice);
	cudaMemcpy(d_vec2,h_vec2,BYTES,cudaMemcpyHostToDevice);

	// lauch kernel
	add<<<num_blocks,num_threads>>>(d_vec1,d_vec2,d_vec3);

	// move result back to main memory
	cudaMemcpy(h_vec3,d_vec3,BYTES,cudaMemcpyDeviceToHost);

	//print result
	for(i=0;i<SIZE;i++)
		printf("%d ", h_vec3[i]);

}