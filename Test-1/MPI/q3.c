// Write a MPI program where each processor sends an integer number and its rank to the master
// processor, where the master gathers all the information and prints the data accordingly

#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define SIZE 2

int main(int narg,char** args)
{
	int rank,procs,i;
	int send_buf[SIZE];
	int rev_buf[32];

	MPI_Init(&narg,&args);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	send_buf[0] = rank;
	send_buf[1] = rank+10; 

	MPI_Gather(send_buf,SIZE,MPI_INT,rev_buf,SIZE,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0)
		for(i=0;i<SIZE*procs;i++)
			printf("%d ",rev_buf[i]);
	
	MPI_Finalize();
	printf("\n");
}