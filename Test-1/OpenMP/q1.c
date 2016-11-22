/*Write an OpenMP program to perform addition of two arrays A & B store the
result in the array C
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100
#define NUM_THREADS 4

int main()
{
	int a[N],b[N],c[N];
	int i;

	//set number of threads
	omp_set_num_threads(NUM_THREADS);

	//storing rand values
	for(i=0;i<N;i++)
	{
		a[i] = rand()%20;
		b[i] = rand()%20;
		c[i] = 0;
	}

	//adding arrays 
	#pragma omp parallel for schedule(static)
		for(i=0;i<N;i++)
			c[i] = a[i] + b[i];

	for(i=0;i<N;i++)
		printf("%d\n",c[i]);
}