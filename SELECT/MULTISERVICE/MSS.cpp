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
#define MAX_SERVICES 30
using namespace std;

char mainFIFO[] = "./mainFIFO"; 
char t1FIFO[] = "./t1FIFO";  
char t2FIFO[] = "./t2FIFO";
char s4FIFO[] = "./s4FIFO" ;
char s5FIFO[] = "./s5FIFO";
char mBuffer[BUFFER_SIZE]; char t1Buffer[BUFFER_SIZE]; char t2Buffer[BUFFER_SIZE];

set<string> clients;

void service1(string clientName){
	printf("Service 1 given to client %s by server \n",clientName.c_str() );
	return;
}

void service2(string clientName){
	printf("Service 2 given to client %s by server \n",clientName.c_str() );
	return;
}

void service3(string clientName){
	printf("Service 3 given to client %s by server \n",clientName.c_str() );
	return;
}

void initialize(){
	int ret = mkfifo(mainFIFO,0666);
	if(ret<0){
		printf("Error in creating main FIFO \n"); exit(0);
	}
	else{
		printf("Main FIFO created successfully \n");
	}

	ret = mkfifo(t1FIFO,0666);
	if(ret<0){
		printf("Error in creating t1 FIFO \n"); exit(0);
	}
	else{
		printf("t1 FIFO created successfully \n");
	}

	ret = mkfifo(t2FIFO,0666);
	if(ret<0){
		printf("Error in creating t2 FIFO \n"); exit(0);
	}
	else{
		printf("t2 FIFO created successfully \n");
	}

	ret = mkfifo(s4FIFO,0666);
	if(ret<0){
		printf("Error in creating s4 FIFO \n"); exit(0);
	}
	else{
		printf("s4 FIFO created successfully \n");
	}
}
int main(int argc, char const *argv[])
{
	
	initialize();
	int ret,mfd,t1fd,t2fd,s4fd;

	mfd = open(mainFIFO,O_RDONLY|O_NONBLOCK); t1fd = open(t1FIFO,O_RDONLY|O_NONBLOCK); t2fd = open(t2FIFO,O_RDONLY|O_NONBLOCK);

	s4fd = open(s4FIFO,O_WRONLY|O_NONBLOCK);
	int sret,l=0;
	fd_set readfds;
	struct timeval timeout;


	while(1)
	{
		FD_ZERO(&readfds);
		FD_SET(mfd,&readfds); FD_SET(t1fd,&readfds); FD_SET(t2fd,&readfds);

		timeout.tv_sec = 10; timeout.tv_usec = 0;
		printf("Selecting the readfds \n");
		sret = select(MAX_SERVICES,&readfds,NULL,NULL,&timeout);

		if(sret==0){
			printf("sret = %d \n",sret );
			printf("Timeout \n");
		}
		else{
			printf("Number of bits set = %d \n",sret );
			
			if(FD_ISSET(mfd,&readfds)){
				ret = read(mfd,mBuffer,BUFFER_SIZE);
				printf("ret in mFIFO read = %d\n",ret );
				if(ret!=-1){
					printf("Client %s wants to join \n",mBuffer );
				}

				string clientName(mBuffer); clients.insert(clientName); printf("%s client inserted successfully\n",clientName.c_str() );
			}
			if(FD_ISSET(t1fd,&readfds)){
				printf("Inside FD_ISSET of service1 or service2 or service3 \n");
				ret = read(t1fd,t1Buffer,BUFFER_SIZE);
				printf("ret in t1 FIFO  = %d\n",ret );
				if(ret!=-1){
					printf("buffer read from t1 FIFO  = %s\n",t1Buffer );
				}
				string info(t1Buffer),clientName,clientID,service; stringstream ss; ss<<info; ss>>clientName; ss>>clientID; ss>>service;

				if(clients.find(clientName)!=clients.end()){
					if(service=="service1"){
						service1(clientName);
					}
					if(service=="service2"){
						service2(clientName);
					}
					if(service=="service3"){
						service3(clientName);
					}
					
				}
				else{
					printf("Client %s not registered. Can't Provide service \n",clientName.c_str());
				}
			}

			if(FD_ISSET(t2fd,&readfds)){
				printf("Inside FD_ISSET of service4 \n");
				ret = read(t2fd,t2Buffer,BUFFER_SIZE);
				printf("ret in t2 FIFO  = %d\n",ret );
				if(ret!=-1){
					printf("buffer read from t2 FIFO = %s\n",t2Buffer );
				}
				string info(t2Buffer),clientName,clientID,service; stringstream ss; ss<<info; ss>>clientName; ss>>clientID; ss>>service;
				printf("Checking presence of client %s \n",clientName.c_str() );
				if(clients.find(clientName)!=clients.end()){
					printf("Writing in buffer %s\n",s4FIFO );
					string msg = clientName+" "+clientID;
					s4fd = open(s4FIFO,O_WRONLY);
					if(s4fd<0){
						printf("Error in opening s4FIFO \n"); exit(0);
					}
					write(s4fd,msg.c_str(),100);
					printf("%s Written successfully in s4 FIFO \n",msg.c_str());
					close(s4fd);
				}
				else{
					printf("Client %s not registered. Can't Provide service \n",clientName.c_str());
				}
			}

		} 
	} 

	return 0;
}