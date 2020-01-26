#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>

#define PORT 8080
using namespace std;

int main(int argc, char const *argv[])
{
	int sfd = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in p1addr,p2addr;
	socklen_t addrlen = sizeof p1addr;
	p1addr.sin_family = AF_INET;
	p1addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	p1addr.sin_port = htons(PORT);
	bind(sfd,(struct sockaddr*)&p1addr,sizeof(p1addr));
	char buffer[100];
	while(1)
	{
		recvfrom(sfd,buffer,100,0,(struct sockaddr*)&p2addr,(socklen_t*)&addrlen);
		printf("Message received : %s \n",buffer );
	}
	return 0;
}
