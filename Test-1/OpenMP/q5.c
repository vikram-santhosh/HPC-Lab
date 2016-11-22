#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

int main ()
{

	int nthreads, tid, procs, maxt, isParallel, isDynamic, isNested;
	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel 
	{
		#pragma omp master
		{
			printf("Obtaining environment variables");

			procs = omp_get_num_procs();
			nthreads = omp_get_num_threads();
			maxt = omp_get_max_threads();
			isParallel = omp_in_parallel();
			isDynamic = omp_get_dynamic();
			isNested = omp_get_nested();

			printf("Number of Processors = %d\n", procs);
			printf("Number of Threads = %d\n", nthreads);
			printf("Max number of threads = %d\n", maxt);
			printf("Is this a parallel regin  ? : %d\n", isParallel);
			printf("Can the number of threads be adjusted in runtime ? : %d\n", isDynamic);
			printf("Is Nested parallelism enabled ? : %d\n", isNested);
		}
	}
}