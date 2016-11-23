// Write an OpenMP program to multiply two matrices A & B and find the
// resultant matrix C


#include <stdio.h>
#include <omp.h>

#define N 100
#define NUM_THREADS 4


int main()
{
	int A[N][N],B[N][N],res[N][N];
	int i,j,k,chunk;

	double start_time,end_time; // optional
	double time_spent;			// optional

	omp_set_num_threads(NUM_THREADS);

	chunk = N / NUM_THREADS;

	for(i=0;i<N;i++)
	{	
		for(j=0;j<N;j++)
		{
			A[i][j] = 1;  // I used 1 cause its easy to verify
			B[i][j] = 1;
			res[i][j] = 0; 
		}
	}	

	start_time = omp_get_wtime();

	#pragma omp parallel shared(A,B,res) private(i,j,k) 
	{
		#pragma omp for schedule(static,chunk)  // even if you don't specify schdule its fine
			for(i=0;i<N;i++)
				for(j=0;j<N;j++)
					for(k=0;k<N;k++)
						res[i][j] += A[i][k] * B[k][j]; 

	}

	end_time = omp_get_wtime();

	//display

	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			printf("%d ",res[i][j]);
		}
		printf("\n");
	}

	time_spent = (double) end_time - start_time ;

	printf("Time spend in multiplication : %lf\n",time_spent);
}
