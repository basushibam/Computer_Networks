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
	int usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_DGRAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strcpy(userv_addr.sun_path, ADDRESS);

	userv_len = sizeof(userv_addr);
	struct sockaddr_in maddr; size_t len;
	maddr.sin_family = AF_INET;
	maddr.sin_port = htons(8088);
	maddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	printf("Sending my address %s : %d \n",inet_ntoa(maddr.sin_addr),ntohs(maddr.sin_port) );
	sleep(5);
	sendto(usfd , (struct sockaddr*)&maddr , sizeof(maddr) , 0 , ( struct sockaddr * ) &userv_addr ,  sizeof(ucli_addr));
	printf("Sent\n");
	while(1);
	//recvfrom(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &ucli_addr , & uscli_len );
	return 0;
}
