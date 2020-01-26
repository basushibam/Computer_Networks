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
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_DGRAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	cli_len = sizeof(cli_addr);

	
	//sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &cli_addr ,  cli_len);
	while(1)
	{
		char buffer[100]; memset(buffer,0,sizeof(buffer));

		recvfrom(sfd , buffer , 100 , 0 , ( struct sockaddr * ) &cli_addr , & cli_len );
		printf("Message received from client at %s:%d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
		printf("Message : %s \n",buffer );
		for(int i=0;buffer[i];i++) buffer[i]=toupper(buffer[i]);
		cli_len = sizeof(cli_addr);
		printf("Sending message %s \n",buffer );
		
		sendto(sfd,buffer,100,0,(struct sockaddr*)&cli_addr,cli_len);
		printf("Message sent to client successfully\n");	
		sleep(10);
	}
	return 0;
}