// Write an OpenMP program to find prime numbers (split)

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 100
#define NUM_THREADS 4
#define FALSE 0
#define TRUE 1

int main()
{
	int isPrime[N+1] ,i,j;

	for(j=0;j<=N;j++)
		isPrime[j] = TRUE;

	isPrime[0] = isPrime[1] = FALSE;

	omp_set_num_threads(NUM_THREADS);

	i = 2; // first prime number

	while(i*i <= N )
	{
		if(isPrime[i])
		{
			#pragma omp parallel for
			for(j=i*2;j<=N;j+=i)
			{
				isPrime[j] = FALSE;
			}
		}

		i++;
	}

	for(i=0;i<=N;i++)
		if(isPrime[i])
			printf("%d ",i);
}