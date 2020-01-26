#include <bits/stdc++.h>
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

using namespace std;
#define PORT 8080

int main(int argc, char const *argv[])
{
	

	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no= PORT;

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
		{
			printf("Error in accpting \n");
			perror("accept ");
		}
		else
		{
			printf("\n accept successful");
			printf("Connection accepted from %s : %d which is a group1 process \n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
			
			char buffer[100];
			recv(nsfd,buffer,100,0);
			printf("Received message in BS : %s \n",buffer );
			string s(buffer); stringstream ss; ss<<s;
			string g2process,port; ss>>g2process; ss>>port;
			printf("And wants to connect to process %s of group2 and send port %s \n",g2process.c_str(),port.c_str() );
			sleep(5);
			struct sockaddr_in taddr; socklen_t t;
			getpeername(nsfd,(struct sockaddr*)&taddr,&t);
			string packet(inet_ntoa(taddr.sin_addr)); packet+=" "; packet+=port;			
			int p7fd;
			struct sockaddr_in p7_addr;
			

			bzero(&p7_addr,sizeof(serv_addr));

			if((p7fd = socket(AF_INET , SOCK_STREAM , 0))==-1)
			perror("\n socket");
			else printf("\n socket created successfully\n");

			p7_addr.sin_family = AF_INET;
			p7_addr.sin_port = htons(8087);
			p7_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

			if(connect(p7fd , (struct sockaddr *)&p7_addr , sizeof(p7_addr))==-1)
			perror("\n connect : ");
			else printf("\nconnect to Group 2 Process succesful ");
			printf("Sending packet %s to p7 \n",packet.c_str() );
			send(p7fd,packet.c_str(),100,0);
		} 
	

	

	return 0;
}