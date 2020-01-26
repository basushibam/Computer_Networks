

int MPI_Send(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm) 

buf -  address of send buffer				//Data parameters 
count - number of items to send 			//Data parameters 
datatype - datatype of each items 			//Data parameters 
dest -	rank of destination process 		//Envelope parameters
tag - message tag							//Envelope parameters
comm - communicator 						//Envelope parameters






int MPI_Recv(void *buf,int count,MPI_Datatype datatype,int src,int tag,MPI_Comm comm,MPI_Status *status) 

buf -  address of send buffer				//Data parameters 
count - number of items to send 			//Data parameters 
datatype - datatype of each items 			//Data parameters 
src -	rank of source process 				//Envelope parameters
tag - message tag							//Envelope parameters
comm - communicator 						//Envelope parameters
status - status after operation 			//Envelope parameters


int MPI_Barrier(MPI_Comm comm); //returns only after all the processes have called this function


int Root = 0;
int MPI_Bcast(void *buf,int count,MPI_Datatype datatype,int src,MPI_Comm comm); //Sends the data stored in the buffer buf to all processes having source src
MPI_Bcast(message,BUFFER_SIZE,MPI_CHAR,Root,MPI_COMM_WORLD);_

//The src process sends a differenct part of sendbuf to each process including itself. Process i receives sendcount contiguios elements startignfrom i * sendcount. The received data are stored in recvbuf
//If number of messages is divisible be number of processes then scatter is possible.
int MPI_Scatter(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int dest,MPI_Comm comm)



//The opposite of scatter. Every process, including dest sends data stored in sendbuf to dest. 
int MPI_Gather(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int dest,MPI_Comm comm)



//Combines the elements stored in the sendbuf of each process using operation op and sends the message to recvbuf of the process having rank dest
int MPI_Reduce(void *sendbuf,void *recvbuf, int count,MPI_Datatype datatype,MPI_OP op,int dest,MPI_Comm comm);


#include <mpi.h>
int main(int argc, char const *argv[])
{
	int p,myrank;	//rank varies from 0 - 9999
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Comm_rank()
	return 0;
}


MPI Blocking Send and Receive :

The sending and receiving of messages between pair of precessors.
Blocking send - returns only after the corresponding RECEIVE operation has been 