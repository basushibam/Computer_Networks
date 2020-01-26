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
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	//inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char buffer[100];
	while(1)
	{
		printf("Enter a message to be sent \n");
		scanf("%s",buffer);
		sendto(sfd,buffer,100,0,(struct sockaddr*)&addr,addrlen);		
	}
	return 0;
}
