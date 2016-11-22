/*
Write an OpenMP program which performs C=A+B & D=A-B in separate blocks/sections where
A,B,C & D are arrays.
*/
#include <stdio.h>
#include <omp.h>

#define N 100
#define NUM_THREADS 4

int main()
{
	int A[N],B[N],C[N],D[N];
	int i; // loop-varible

	for(i=0;i<N;i++)
	{
		A[i] = 2*i;
		B[i] = i;
		C[i] = D[i] = 0;
	}

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel shared(A,B,C,D) private(i)
	{

		#pragma omp master 
		{
			printf("Number of threads : %d\n",omp_get_num_threads());
		}

		#pragma omp sections nowait
		{
			#pragma omp section 
			{
				#pragma omp parallel for
				for(i=0;i<N;i++)
					C[i] = A[i] - B[i];
			}
			#pragma omp section
			{
				#pragma omp parallel for
				for(i=0;i<N;i++)
					D[i] = A[i] + B[i];
			}
		}
	}

	for(i=0;i<N;i++)
	{
		printf("C[%d] = %d \n",i,C[i]);
		printf("D[%d] = %d \n",i,D[i]);
	}
}