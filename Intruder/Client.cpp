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
#include<pcap.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	if(argc!=2)
	{printf("\n usage ./a.out port_no"); exit(0);}

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);
	char buffer[256];

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_DGRAM , 0))==-1)
	{perror("\n socket"); exit(0);}
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	socklen_t serv_len = sizeof(serv_addr);
	while(1)
	{
		char buffer[100]; memset(buffer,0,sizeof(buffer));
		char reply[100]; memset(reply,0,sizeof(reply));
		printf("Enter a message for server \n");
		scanf("%s",buffer);
		printf("Sending message : %s \n",buffer );
		sendto(sfd , buffer ,100 , 0 , ( struct sockaddr * ) &serv_addr ,  serv_len);
		printf("Receiving message from somewhere \n");
		struct sockaddr_in naddr; socklen_t len=sizeof(naddr);
		recvfrom(sfd , reply , 100 , 0 , ( struct sockaddr * ) &naddr , & serv_len );
		printf("Message received : %s \n",reply);
		printf("Message received from %s:%d\n",inet_ntoa(naddr.sin_addr),ntohs(naddr.sin_port) );
	}
	
	
	return 0;
}