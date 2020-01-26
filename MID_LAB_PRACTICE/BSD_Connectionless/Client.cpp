#include<time.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/select.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<arpa/inet.h>

#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);
	char buffer[100];

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_DGRAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	socklen_t serv_len = sizeof(serv_addr);
	
	while(1)
	{
		string s;
		printf("Enter a message : "); cin>>s;
		sendto(sfd , s.c_str() , 100 , 0 , ( struct sockaddr * ) &serv_addr ,  serv_len);
		recvfrom(sfd , buffer , 100 , 0 , ( struct sockaddr * ) &serv_addr , & serv_len );
		printf("message received : %s \n",buffer );
	}
	
	return 0;
}