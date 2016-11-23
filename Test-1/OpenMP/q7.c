//Write an OpenMP program to find the largest element in an array using locks.

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 1000
#define NUM_THREADS 4


int main()
{
	int arr[N],i;
	int max = -1;

	omp_lock_t lock;
	omp_init_lock(&lock);
	
	omp_set_num_threads(NUM_THREADS);

	for(i=0;i<N;i++)
		arr[i] = rand()%100000;


	#pragma omp parallel for
	for(i=0;i<N;i++)
	{
		if(arr[i]>max)
		{
			omp_set_lock(&lock);
			if(arr[i]>max)
				max = arr[i];
			omp_unset_lock(&lock);
		}
	}

	printf("Max = %d\n",max);
}
