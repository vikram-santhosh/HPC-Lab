// Write an MPI program where the master processor broadcasts a message “HELLO MSRIT” to the
// remaining processors using broadcast system call.

#include <stdio.h>
#include <mpi.h>
#include <string.h>

#define SIZE 32

int main(int nargs,char** args)
{
	int procs,rank;
	char msg_buf[SIZE];
	int root = 0;
	
	MPI_Init(&nargs,&args);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
	{
		strcpy(msg_buf,"Hello Flintstone!");
	}

	MPI_Bcast(msg_buf,SIZE,MPI_CHAR,root,MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);

	printf("Process - %d says %s \n", rank, msg_buf );
	
	MPI_Finalize();
	
}
