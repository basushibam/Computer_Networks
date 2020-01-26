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

#define ADDRESS  "mysocket"

int main(int argc, char const *argv[])
{
	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_DGRAM , 0);
	perror("socket");

  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS);
	unlink(ADDRESS);
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");
	struct sockaddr_in taddr;
	//fgets( buffer , 256 , stdin );
	//sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &userv_addr ,  userv_len);
	recvfrom(usfd , (struct sockaddr*)&taddr ,sizeof (taddr) , 0 , ( struct sockaddr * ) &userv_addr , & userv_len );
	printf("Address to get connected to =  %s : %d \n",inet_ntoa(taddr.sin_addr),ntohs(taddr.sin_port) );
	return 0;
}