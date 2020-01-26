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
	

	int bsfd;
	struct sockaddr_in serv_addr;
	int port_no=PORT;
	socklen_t len;
	bzero(&serv_addr,sizeof(serv_addr));

	if((bsfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(bsfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful to bypass server ");
	struct sockaddr_in taddr;
	getsockname(bsfd,(struct sockaddr*)&taddr,&len);
	printf("My IP:PORT = %s : %d \n",inet_ntoa(taddr.sin_addr),ntohs(taddr.sin_port) );
	
	string packet("P7"); packet+=" "; packet+="8082";
	printf("Sending packet %s to bypass server \n",packet.c_str() );
	send(bsfd,packet.c_str(),100,0);
	int sfd;
	struct sockaddr_in ser_addr,cli_addr;
	socklen_t cli_len;
	port_no=8082;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("socket ");
	else printf("socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(8082);
	string IP = inet_ntoa(taddr.sin_addr);
	cout<<"IP = "<<IP<<endl;
	ser_addr.sin_addr.s_addr = inet_addr(IP.c_str());

	if(bind(sfd,(struct sockaddr *) &ser_addr,sizeof(ser_addr))==-1)
	perror("bind : ");
	else printf("bind successful ");
	printf("Hello \n");
	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept ");
	else
	{
		printf("\n accept successful");
		printf("Connection accepted from P7 %s : %d \n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
		while(1)
		{
			char buffer[100]; recv(nsfd,buffer,100,0);
			printf("Received message : %s \n",buffer );
			printf("Enter a message : "); string s; cin>>s;
			send(nsfd,s.c_str(),100,0);
		}
	}


	return 0;
}