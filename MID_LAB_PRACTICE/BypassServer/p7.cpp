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

int main(int argc, char const *argv[])
{
	int sfd;
	struct sockaddr_in p7_addr,cli_addr;
	socklen_t cli_len;
	int port_no= 8087;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&p7_addr,sizeof(p7_addr));

	p7_addr.sin_family = AF_INET;
	p7_addr.sin_port = htons(port_no);
	p7_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sfd,(struct sockaddr *) &p7_addr,sizeof(p7_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	listen(sfd,10);
	int nsfd;
	printf("Listening to connection intimation from a process of group 1 through bypass server \n");
	nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len);
	printf("successfully accepted connection request from bypass server %s : %d \n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port) );
		char buffer[100];
		recv(nsfd,buffer,100,0);
		printf("P7 received : %s \n",buffer );
		string packet(buffer); stringstream ss; ss<<packet;
		string ip,port; ss>>ip; ss>>port;
		cout<<"P7 has to connect to IP = "<<ip<<" and port = "<<port<<endl;
			int p2fd;
			struct sockaddr_in p2_addr;
			

			bzero(&p2_addr,sizeof(p2_addr));

			if((p2fd = socket(AF_INET , SOCK_STREAM , 0))==-1)
			perror("\n socket");
			else printf("\n socket created successfully\n");

			p2_addr.sin_family = AF_INET;
			p2_addr.sin_port = htons(atoi(port.c_str()));
			p2_addr.sin_addr.s_addr = inet_addr(ip.c_str());

			if(connect(p2fd , (struct sockaddr *)&p2_addr , sizeof(p2_addr))==-1)
			perror("\n connect : ");
			else printf("\nconnect to Group 1 Process P2 succesful ");
			while(1)
			{
				string s;
				printf("Enter a message : "); cin>>s;
				send(p2fd,s.c_str(),100,0);
				char buffer[100]; recv(p2fd,buffer,100,0);
				printf("Message received : %s \n", buffer); 
			}
	return 0;
}