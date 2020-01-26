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

int mtamtaport,muamtaport;

void* listenToMTA(void* args)
{
	int nsfd;
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in my_addr; socklen_t len = sizeof(my_addr);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	my_addr.sin_port = htons(mtamtaport);
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
    	printf("MTA Listening for other MTA\n");
    	struct sockaddr_in newaddr; socklen_t len;
    	nsfd = accept(sfd, (struct sockaddr *)&newaddr, &len);
	    printf("Connection accepted from MTA at %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
	    if (nsfd<0)
	    {
	       	perror("Error in accepting \n");
	        exit(EXIT_FAILURE);
	    }
	    int muaport;
	    char message[100];
	    recv(sfd,message,100,0);
	    string Msg(message);
	    stringstream ss; ss<<Msg; ss>>muaport ; ss>>muaport;
	    int sfd2 = socket(AF_INET,SOCK_STREAM,0);
		
		struct sockaddr_in server_addr; socklen_t len1 = sizeof(server_addr);
		server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		server_addr.sin_port = htons(muaport);
		server_addr.sin_family=AF_INET;
		ret = connect(sfd2,(struct sockaddr*)&server_addr,len1);
		if(ret<0)
		{
			perror("Connection failed\n"); exit(0);
		}
		printf("Connected to MUA \n");
		send(sfd2,message,100,0); 
		    cout<<"Message : "<<message<<endl;
	    }
    pthread_exit(0);

}

void* listenToMUA(void* args)
{
	int nsfd;
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in my_addr; socklen_t len = sizeof(my_addr);
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	my_addr.sin_port = htons(muamtaport);
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
    	printf("MTA Listening for MUA\n");
    	struct sockaddr_in newaddr; socklen_t len;
    	nsfd = accept(sfd, (struct sockaddr *)&newaddr, &len);
	    printf("Connection accepted from MUA at %s : %d \n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port) );
	    if (nsfd<0)
	    {
	       	perror("Error in accepting \n");
	        exit(EXIT_FAILURE);
	    }
	    int mtaport;
	    char message[100];
	    recv(sfd,message,100,0);
	    string Msg(message);
	    cout<<"Message received from MUA = "<<message<<endl;
	    stringstream ss; ss<<Msg; ss>>mtaport ; 
	    int sfd2 = socket(AF_INET,SOCK_STREAM,0);
		
		struct sockaddr_in server_addr; socklen_t len1 = sizeof(server_addr);
		server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		server_addr.sin_port = htons(mtaport);
		server_addr.sin_family=AF_INET;
		ret = connect(sfd2,(struct sockaddr*)&server_addr,len1);
		if(ret<0)
		{
			perror("Connection failed\n"); exit(0);
		}
		printf("Connected to MTA \n");
		send(sfd2,message,100,0); 
		    cout<<"Message sent to mta at "<<mtaport<<" : "<<message<<endl;
	}
    pthread_exit(0);

}

int main(int argc, char const *argv[])
{
	if(argc<3)
	{
		printf("Usage <%s> <mta_mta_port> <mua_mta_port>\n",argv[0] ); exit(0);
	}
	mtamtaport=atoi(argv[1]);
	muamtaport=atoi(argv[2]);
	pthread_t t1,t2;
	pthread_create(&t1,NULL,listenToMTA,NULL);
	pthread_create(&t2,NULL,listenToMUA,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}