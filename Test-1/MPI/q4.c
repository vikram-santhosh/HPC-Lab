// Write a MPI program to find sum of 'n' integers on 'p' processors using point-to-point
// communication libraries call

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int narg,char** args)
{
	int procs,rank;
	int sum = 0,i,val;
	int root = 0, msg_tag = 0;
	MPI_Status status;

	MPI_Init(&narg,&args);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	//send rank to root
	if(rank!=root)
		MPI_Send(&rank,1,MPI_INT,root,msg_tag,MPI_COMM_WORLD);

	else
	{
		for(i=1;i<procs;i++)
		{
			MPI_Recv(&val,1,MPI_INT,i,msg_tag,MPI_COMM_WORLD,&status);
			sum += val;
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);

	if(rank == 0)
		printf("Sum = %d\n",sum);

	MPI_Finalize();
}