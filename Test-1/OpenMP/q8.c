//Write an OpenMP program to show how thread private clause works

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define NUM_THREADS 4

int x,y,idx;

int main()
{
	omp_set_num_threads(NUM_THREADS);

	#pragma omp threadprivate(x)

	printf("Entering Private Section-I \n");

	#pragma omp parallel private(idx,y)
	{
		idx = omp_get_thread_num();
		x = idx;
		y = 10;
		printf("Thread-%d \n Private : %d \t ThreadPrivate : %d\n", idx ,y,x);
	}

	printf("Entering Private Section-II \n");

	#pragma omp parallel private(idx,y)
	{
		idx = omp_get_thread_num();
		y = 100;
		printf("Thread-%d \n Private : %d \t ThreadPrivate : %d\n", idx ,y,x);
	}
}