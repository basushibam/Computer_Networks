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
#include <bits/stdc++.h>
#include<errno.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ether.h>
#include<netinet/udp.h>
#define ADDRESS  "/tmp/fd-pass.socket"

using namespace std;

void handle_error(string msg) {do { perror(msg.c_str()); exit(EXIT_FAILURE); } while(0);}




static
int * recv_fd(int socket, int n) {
        int *fds = (int*)malloc (n * sizeof(int));
        struct msghdr msg = {0};
        struct cmsghdr *cmsg;
        char buf[CMSG_SPACE(n * sizeof(int))], dup[256];
        //memset(buf, ‘\0’, sizeof(buf));
        struct iovec io = { .iov_base = &dup, .iov_len = sizeof(dup) };

        msg.msg_iov = &io;
        msg.msg_iovlen = 1;
        msg.msg_control = buf;
        msg.msg_controllen = sizeof(buf);
        
        if (recvmsg (socket, &msg, 0) < 0)
                handle_error ("Failed to receive message");

        cmsg = CMSG_FIRSTHDR(&msg);

        memcpy (fds, (int *) CMSG_DATA(cmsg), n * sizeof(int));

        return fds;
}

int main()
{
	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	socklen_t userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	// perror("socket");
	if (usfd == -1)
                handle_error ("Failed to create socket");

    if (unlink ("/tmp/fd-pass.socket") == -1 && errno != ENOENT)
                handle_error ("Removing socket file failed");
  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strncpy(userv_addr.sun_path, "/tmp/fd-pass.socket",  sizeof(userv_addr.sun_path));
	
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");
	else printf("bind successful\n");
	 if (listen(usfd, 5) == -1)
                handle_error ("Failed to listen on socket");
         printf("Accepting the new connection \n");

    int nsfd = accept(usfd, NULL, NULL);
        printf("nsfd = %d \n",nsfd );
        if (nsfd == -1)
                handle_error ("Failed to accept incoming connection");

       int* afd = recv_fd (nsfd,1);
       int rfd = afd[0];      

	
	
	printf("rfd = %d \n",rfd );
	char ch;
	while(read(rfd,&ch,1)>0) 
	{
		printf("%c",ch );
	}
}