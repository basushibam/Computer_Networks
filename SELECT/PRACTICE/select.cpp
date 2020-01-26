#include <bits/stdc++.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 100
#define MAX_CLIENTS 5
#define LOOPS 20
using namespace std;

int main(int argc, char const *argv[])
{
	int fd1,fd2,ret,sret,l=0;
	fd_set readfds;
	struct timeval timeout;
	char buffer[BUFFER_SIZE];

	fd1 = open("./f1.txt",O_RDONLY); 
	fd2 = open("./f2.txt",O_RDONLY);

	while(l++<LOOPS){
		FD_ZERO(&readfds);
		FD_SET(fd1,&readfds); FD_SET(fd2,&readfds);

		timeout.tv_sec = 0.5; timeout.tv_usec = 0;

		sret = select(MAX_CLIENTS,&readfds,NULL,NULL,&timeout);

		if(sret==0){
			printf("sret = %d \n",sret );
			printf("Timeout \n");
		}
		else
		{
			memset((void*)buffer,0,BUFFER_SIZE);
			if(FD_ISSET(fd1,&readfds)){
				ret = read(fd1,buffer,BUFFER_SIZE);
				printf("ret = %d\n",ret );
				if(ret!=-1){
					printf("buffer = %s\n",buffer );
				}
			}
			else if(FD_ISSET(fd2,&readfds)){
				ret = read(fd2,buffer,BUFFER_SIZE);
				printf("ret = %d\n",ret );
				if(ret!=-1){
					printf("buffer = %s\n",buffer );
				}
			}
		}
	}

	return 0;
}