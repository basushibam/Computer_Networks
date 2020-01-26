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
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");
	struct sockaddr_in raddr; socklen_t len;
	getsockname(sfd,(struct sockaddr*)&raddr,&len);
	printf("Connection accepted through getsockname() from %s : %d \n",inet_ntoa(raddr.sin_addr),ntohs(raddr.sin_port) );
			
	listen(sfd,10);
	while(1)
	{
		int nsfd;
		if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
		{
			printf("Error in accepting \n");
			perror("\n accept ");
		}
		
		else
		{
			printf("\n accept successful");
			printf("Connection accepted from %s : %d \n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
			struct sockaddr_in naddr; socklen_t len;
			getsockname(nsfd,(struct sockaddr*)&naddr,&len);
			printf("Connection accepted through getsockname() %s : %d \n",inet_ntoa(naddr.sin_addr),ntohs(naddr.sin_port) );
			getpeername(nsfd,(struct sockaddr*)&naddr,&len);
			printf("Client address through getpeername() is %s : %d \n",inet_ntoa(naddr.sin_addr),ntohs(naddr.sin_port) );

			char buffer[100];
			
			recv(nsfd,buffer,100,0);
			printf("Recived %s \n",buffer);
			for(int i=0;i<strlen(buffer);i++) buffer[i]=toupper(buffer[i]);
			printf("Sending %s \n",buffer);
			send(nsfd,buffer,100,0);		
		} 
	}
	
	return 0;
}