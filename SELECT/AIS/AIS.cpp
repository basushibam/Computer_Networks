#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 100
#define MAX_CLIENTS 5
#define LOOPS 20
using namespace std;

char buffer[BUFFER_SIZE];

void signalHandler(int signal){
	printf("Signal Received \n");
	char pipeForP4[] = "./pipeForP4";
	printf("Readirecting input to p4 = %s\n",buffer );
	int fd = open(pipeForP4,O_WRONLY);
	if(fd<0){
			printf("Error in opening fifo in AIS \n"); exit(0);
		}

	write(fd,buffer,BUFFER_SIZE);
	close(fd);
}


int main(int argc, char const *argv[])
{
	signal(SIGUSR1,signalHandler);
	char ans = 'n';
	int ret = mkfifo("./client1",0666);
	
	if(ret<0){
		printf("Error in creating client 1 fifo in AIS process \n"); exit(0);}
	else {
		printf("Successfully created fifo for client 1 \n");
	}

	printf("Process ID of AIS process = %d \n",getpid() ); 
	printf("Continue? y/n\n");
	scanf("%c",&ans);
	
	
	int fd1 = 0;
	int fd2 = open("./client1",O_RDONLY);
	printf("FD2 of client 1 = %d \n",fd2 );


	int sret,l=0;
	fd_set readfds;
	struct timeval timeout;
	

	
	
		
		while(l++<LOOPS){
		
		printf("Parent Loop = %d \n",l );
		FD_ZERO(&readfds);
		FD_SET(fd1,&readfds); FD_SET(fd2,&readfds); 

		timeout.tv_sec = 10; timeout.tv_usec = 0;

		sret = select(MAX_CLIENTS,&readfds,NULL,NULL,&timeout);

		if(sret==0){
			printf("sret = %d \n",sret );
			printf("Timeout \n");
		}
		else
		{
			printf("Number of bits set = %d \n",sret );
			memset((void*)buffer,0,BUFFER_SIZE);
			
			if(FD_ISSET(fd1,&readfds)){
				ret = read(fd1,buffer,BUFFER_SIZE);
				printf("re in self process = %d\n",ret );
				if(ret!=-1){
					printf("buffer read from console input = %s\n",buffer );
				}
			}
			if(FD_ISSET(fd2,&readfds)){
				ret = read(fd2,buffer,BUFFER_SIZE);
				printf("ret in client  = %d\n",ret );
				if(ret!=-1){
					printf("buffer read from client 1 = %s\n",buffer );
				}
			}

		}
		
	
	}
	



	
}