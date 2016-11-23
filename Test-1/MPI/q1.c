/*The code shown below is the calculation of pi by the method of numeric
integration. The algorithm has a loop  which executes a
predetermined number of iterations (num_steps) where a reduction over the
variable ‘sum’ is done. The variable ‘x’ works like a partial result which has
an independent value between iterations. At the end of the  loop, the
operation between ‘step’ and ‘sum’ produces ‘pi’. The number pi will be more
precise if the number of iterations is greater.*/

#include <mpi.h>
#include <stdio.h>

#define NUM_STEPS 10e7

int main(int nargs,char** args)
{
	double height,width,area;
	int num_procs,rank;
	double sum = 0, pi =0,step,dx,i;

	// Initialize communicator, num of procs and rank of procs
	MPI_Init(&nargs,&args);
	MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);


	width = 1.0 / NUM_STEPS;
	MPI_Barrier(MPI_COMM_WORLD);

	for(i = rank+0.5;i<NUM_STEPS;i+=num_procs)
	{
		dx = i * width; 
		height = 4.0 / (1.0 + dx*dx);
		area = height*width;
		sum += area;
	}

	// MPI_Reduce(const void *sendbuf, void *recvbuf, int size, MPI_Datatype datatype,
 	// MPI_Op op, int root, MPI_Comm comm)

	MPI_Reduce(&sum,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

	if(rank==0)
		printf("PI = %lf\n",pi);
	MPI_Finalize();
}

