// Write a MPI program to send the message from a process whose rank=3 to all other remaining
// processes.

#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define SIZE 64

int main(int narg, char** args)
{
	int num_procs,rank,i;
	int msg_tag = 0;
	int sender_rank = 3;
	char msg[SIZE];
	MPI_Status status;

	MPI_Init(&narg,&args);
	MPI_Comm_size(MPI_COMM_WORLD,&num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank == sender_rank)
	{
		strcpy(msg,"Flintstone!");
		for(i=0;i<num_procs;i++)
		{
			MPI_Send(msg,SIZE,MPI_CHAR,i,msg_tag,MPI_COMM_WORLD);
		}
	}

	else
	{
		MPI_Recv(msg,SIZE,MPI_CHAR,sender_rank,msg_tag,MPI_COMM_WORLD,&status);
		printf("Process Rank - %d : %s\n",rank,msg);
	}


	MPI_Finalize();
}