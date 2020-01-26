#include <bits/stdc++.h>
#include<time.h>
#include <sys/uio.h>
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
using namespace std;

int main(int argc, char const *argv[])
{
	
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len=sizeof(cli_addr);
	int port_no=8088;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("bind : ");
	else printf("bind successful ");

	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("accept ");
	else
	{
		printf("accept successful");
		printf("Connection accepted from %s : %d \n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
		struct iovec iov[2];
		readv(nsfd,iov,2);
		char buf1[100],buf2[100];
		strcpy(buf1,(char*)iov[0].iov_base);
		printf("Buf1 size = %d \n",(int)iov[0].iov_len );
		// printf("Buf2 = %s \n",(char*)iov[1].iov_base );
	} 
	return 0;
}