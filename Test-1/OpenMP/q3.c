/* Write an OpenMP program to add all the elements of two arrays A & B each of
size 1000 and store their sum in a variable using reduction clause
*/

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 1000
#define NUM_THREADS 4

int main()
{
	int A[N],B[N];
	int sum = 0,i;

	omp_set_num_threads(NUM_THREADS);

	for(i=0;i<N;i++)
	{
		A[i] = rand()%10;
		B[i] = rand()%10;
	}

	#pragma omp parallel for reduction(+:sum)
	for(i=0;i<N;i++)
		sum += A[i] + B[i];


	printf("Sum = %d \n", sum);
}