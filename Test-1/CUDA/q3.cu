#include <cuda.h>
#include <stdio.h>
#include <stdlib.h>

#define N 32 // dim of matrix


//Fattened matrix multiplication . Kernel does not support x,y addressing
__global__ void mat_multiply(int* d_mat1, int* d_mat2, int* d_mat3, int width)
{
	int k,sum=0;
	int col = blockDim.x * blockIdx.x + threadIdx.x;
	int row = blockDim.y * blockIdx.y + threadIdx.y;

	if(row<width && col<width)
	{
		for(k=0;k<width;k++)
		{
			sum += d_mat1[row*width+k] * d_mat2[k*width+col];
		}
		d_mat3[row*width+col] = sum;
	}

}

int main()
{
	int i,j;
	int SIZE = N*N;
	int BYTES = SIZE*sizeof(int);

	// declare device and host variables
	int h_mat1[N][N] , h_mat2[N][N] , h_mat3[N][N];
	int *d_mat1, *d_mat2, *d_mat3;

	// allocate memory on the device
	cudaMalloc((void**)&d_mat1,BYTES);
	cudaMalloc((void**)&d_mat2,BYTES);
	cudaMalloc((void**)&d_mat3,BYTES);

	// generate matrix on host
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			h_mat1[i][j] = 1;
			h_mat2[i][j] = 1;
			h_mat3[i][j] = 0;
		}
	}

	dim3 dimGrid(1,1);
	dim3 dimBlock(N,N);

	// move variables from host to device
	cudaMemcpy(d_mat1,h_mat1,BYTES,cudaMemcpyHostToDevice);
	cudaMemcpy(d_mat2,h_mat2,BYTES,cudaMemcpyHostToDevice);

	// lauch kernel
	mat_multiply<<<dimGrid,dimBlock>>>(d_mat1,d_mat2,d_mat3,N);
	cudaDeviceSynchronize();

	// move result back to main memory
	cudaMemcpy(h_mat3,d_mat3,BYTES,cudaMemcpyDeviceToHost);

	//print result
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%d ",h_mat3[i][j]);
		}
		printf("\n");
	}

}