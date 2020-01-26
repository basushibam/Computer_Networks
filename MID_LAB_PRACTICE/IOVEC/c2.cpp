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
#include <sys/uio.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
using namespace std;

int main(int argc, char const *argv[])
{
	

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=8088;

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
	char buf1[]="This is buffer 1 "; char buf2[] = "This is buffer 2 ";
	struct iovec iov[2]; iov[0].iov_base=buf1; iov[1].iov_base=buf2;
	iov[0].iov_len = strlen(buf1); iov[1].iov_len = strlen(buf2);
	writev(sfd,iov,2);
	printf("Buffers sent \n");
	return 0;
}