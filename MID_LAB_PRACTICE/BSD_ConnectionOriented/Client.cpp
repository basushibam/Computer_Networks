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
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr,naddr;
	int port_no=atoi(argv[1]);
	socklen_t len;
	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");

	getsockname(sfd,(struct sockaddr*)&naddr,&len);
	printf("getsockname() on sfd in client gives %s : %d  \n",inet_ntoa(naddr.sin_addr),ntohs(naddr.sin_port) );
	getpeername(sfd,(struct sockaddr*)&naddr,&len);
	printf("Client address through getpeername() is %s : %d \n",inet_ntoa(naddr.sin_addr),ntohs(naddr.sin_port) );

	while(1)
	{
		string s; char buffer[100]; 
		
		cout<<"Enter a string "<<endl;
		cin>>s;
		cout<<"Sending : "<<s<<endl;
		send(sfd,s.c_str(),100,0);
		recv(sfd,buffer,100,0);
		printf("Received : %s \n",buffer);
	}
	return 0;
}