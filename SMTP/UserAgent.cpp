#include <bits/stdc++.h>
#include <sys/socket.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include<cstdlib>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include<unistd.h>
#include<pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>		/* For inet_ntoa() and ntohs()*/
using namespace std;

int ret,myport,localmtaport;
string a,b;

void* listenToMTA(void* args)
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in my_addr; socklen_t len = sizeof(my_addr);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	my_addr.sin_port = htons(myport);
	my_addr.sin_family=AF_INET;
	int ret =  bind(sfd, (struct sockaddr *)&my_addr, 
                                 sizeof(my_addr));
    if (ret<0)
    {
        perror("bind failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Server: Binded\n");

    ret = listen(sfd,10);
    while(1)
    {
    	printf("Client Listening for MTA\n");
    	struct sockaddr_in newaddr; socklen_t len;
    	int nsfd = accept(sfd, (struct sockaddr *)&newaddr, &len);
	    printf("Connection accepted from MTA at %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
	    if (nsfd<0)
	    {
	       	perror("Error in accepting \n");
	        exit(EXIT_FAILURE);
	    }
	    char message[100];
	    recv(sfd,message,100,0);
	    cout<<"Message : "<<message<<endl;
    }
    pthread_exit(0);
}

void* sendmsg(void* args)
{
	string friendport,mtaport;
	mtaport=a; friendport=b;
	char message[100];
	while(1)
	{
		
		printf("Enter a message : "); scanf("%s",message);
		int c=fork();
		if(c==0) 
		{
			printf("Forking Message User Agent process #################\n"); break;
		}
	}
	
	string Msg(message);
	string packet = friendport+" "+mtaport+" "+Msg;
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	stringstream ss; ss<<mtaport; ss>>localmtaport;
	struct sockaddr_in server_addr; socklen_t len = sizeof(server_addr);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(localmtaport);
	server_addr.sin_family=AF_INET;
	ret = connect(sfd,(struct sockaddr*)&server_addr,len);
	if(ret<0)
	{
		perror("Connection failed\n"); exit(0);
	}
	printf("Connected to MTA \n");
	send(sfd,packet.c_str(),100,0);
	cout<<"Message sent = "<<packet<<endl;
	printf("Child process exiting ##########################\n");
}

int main(int argc, char *argv[])
{
	if(argc<5)
	{
		printf("Usage <%s> <myport> <localmtaport> <remotemtaport> <friendport>\n",argv[0] ); exit(0);
	}
	myport=atoi(argv[1]);
	localmtaport=atoi(argv[2]);
	string mtaport(argv[3]);
	string friendport(argv[4]);
	a=mtaport; b=friendport;
	pthread_t t1,t2;
	pthread_create(&t1,NULL,listenToMTA,NULL);
	pthread_create(&t2,NULL,sendmsg,NULL);
	pthread_join(t1,NULL); pthread_join(t2,NULL);
	return 0;
}