// Write an OpenMP program to show how first private clause works.(Factorial
// program)


#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 10
#define NUM_THREADS 2

int main()
{
	int fact[N],i,acc=1;
	fact[0] = 1;

	omp_set_num_threads(NUM_THREADS);

	#pragma omp prallel shared(fact)
	{
		#pragma omp parallel for firstprivate(acc) 
		for(i=1;i<N;i++)
		{
			acc = fact[i-1] * i;
			fact[i] = acc;
		}
	}

	for(i=1;i<N;i++)
		printf("%d\n",fact[i]);
}
