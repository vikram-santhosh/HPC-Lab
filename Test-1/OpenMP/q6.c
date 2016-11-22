// Write an OpenMP program to find the largest element in an array using critical section.

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 1000
#define NUM_THREADS 4


int main()
{
	int arr[N],i;
	int max = -1;

	for(i=0;i<N;i++)
		arr[i] = rand()%100000;

	omp_set_num_threads(NUM_THREADS);
	
	#pragma omp parallel for
	for(i=0;i<N;i++)
	{
		if(arr[i]>max)
		{
			#pragma omp critical
			if(arr[i]>max)
				max = arr[i];
		}
	}

	printf("Max = %d\n",max);
}