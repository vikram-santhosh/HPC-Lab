#include <cuda.h>
#include <stdio.h>

__global__ void kernel(void)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	printf("Hello World - Block : %d - Thread : %d - Global Thread ID : %d\n" , 
		blockIdx.x, threadIdx.x,idx);
}

int main()
{
	int num_threads, num_blocks;

	printf("Enter number of blocks and threads per block !\n");
	scanf("%d%d",&num_blocks,&num_threads);

	kernel<<<num_blocks,num_threads>>>();
	cudaDeviceSynchronize();
	printf("Hello World !!\n");

}