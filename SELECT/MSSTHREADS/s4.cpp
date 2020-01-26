#include <bits/stdc++.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>	
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#define BUFFER_SIZE 100

using namespace std;


char s4FIFO[] = "./s4FIFO" ;
vector<string> pipes;
char bufferForServer[BUFFER_SIZE];


int main(int argc, char const *argv[])
{
	printf("Inside s4 program \n"); int l=0;



	



	while(1){
	l++; printf("Running loop %d times \n",l );	
	int fd = open(s4FIFO,O_RDONLY),ret;
	printf("fd value = %d \n",fd );
	if(fd<0){
		printf("Error in opening s4 FIFO in s4 \n"); exit(0);
	}
	printf("s4 FIFO opened successfully \n");
	read(fd,bufferForServer,BUFFER_SIZE);
	close(fd);
	printf("Buffer read = %s \n",bufferForServer );
	string info(bufferForServer),clientName,clientID; stringstream ss; ss<<info; ss>>clientName; ss>>clientID; string clientPipe = "./"+clientName;
	if(find(pipes.begin(),pipes.end(),clientPipe)==pipes.end()){
		printf("Creating pipe %s \n",clientPipe.c_str() );
		ret = mkfifo(clientPipe.c_str(),0666);
		if(ret<0)
		{
			printf("Error in creating pipe %s in s4 \n",clientPipe.c_str() ); exit(0);
		}

		pipes.push_back(clientPipe);
	}
	else{
		printf("%s pipe already created \n",clientPipe.c_str() );
	}
	int pidOfClient;
	stringstream sss; sss<<clientID; sss>>pidOfClient;
	kill(pidOfClient,SIGUSR1);

	
	int wfd = open(clientPipe.c_str(),O_WRONLY);
	if(wfd<0){
		printf("Error in opening %s FIFO in s4 \n",clientPipe.c_str()); exit(0);
	}
	string message = "Service given to client "+ clientName;
	
	write(wfd,message.c_str(),100);
	close(wfd);
	}
	return 0;
}