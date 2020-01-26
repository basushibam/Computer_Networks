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

using namespace std;

char mainFIFO[] = "./mainFIFO"; char t1FIFO[] = "./t1FIFO";	char t2FIFO[] = "./t2FIFO";
string name , service,pid;

void signalHandler(int signal){
	string clientPipe = "./"+name;
	char bufferForS4[BUFFER_SIZE];
	int rfd = open(clientPipe.c_str(),O_RDONLY);
	if(rfd<0){
		printf("Error in opening %s pipe in client \n",clientPipe.c_str() );
	}
	read(rfd,bufferForS4,100);
	printf("Client %s read = %s  \n",name.c_str(),bufferForS4 );
	close(rfd);
}


int main(int argc, char const *argv[])
{
	signal(SIGUSR1,signalHandler);
	int mfd = open(mainFIFO,O_WRONLY|O_NONBLOCK); int t1fd = open(t1FIFO,O_WRONLY|O_NONBLOCK);	int t2fd = open(t2FIFO,O_WRONLY|O_NONBLOCK);
	
	int processID = getpid(); stringstream ss; ss<<processID; ss>>pid; 
	printf("Enter your name  \n"); cin>>name;
	write(mfd,name.c_str(),100); printf("Join request sent \n");
	while(1){
		
		printf("Which service do you want now ? \n"); cin>>service;
		string packet=""; packet = name + " " + pid + " " + service;
		if(service=="service1" or service=="service2" or service=="service3"){
			
			write(t1fd,packet.c_str(),100);
			printf("Packet written = %s \n",packet.c_str() );
		}
		else if(service=="service4"){
			printf("Service 4 if condition \n");
			write(t2fd,packet.c_str(),100);
			printf("Packet written = %s \n",packet.c_str() );
		}
		else {
			printf("Service %s not available \n",service.c_str() );
		}
	}
	close(t2fd);
	return 0;
}