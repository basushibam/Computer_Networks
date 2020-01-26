#include <bits/stdc++.h>
#include <ace/Reactor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/SOCK_Connector.h>
#include <ace/SOCK_Stream.h>
#include <ace/Thread.h>
#include <ace/Synch.h>
#include <ace/Log_Msg.h>
#include <ace/streams.h>
#include <ace/INET_Addr.h>
#include <errno.h>
using namespace std;

#define MAX_CLIENTS 10
#define MAX_BUFFER_SIZE 100

ACE_SOCK_Stream client_stream[MAX_CLIENTS];
int cid[MAX_CLIENTS];
int total_clients=0;

void* serve(void* arg)
{
	int clien_id = *(int*)arg;
	char buffer[MAX_BUFFER_SIZE];
	while(1)
	{
		client_stream[clien_id].recv_n(buffer,MAX_BUFFER_SIZE,0);
		printf("Server received from client %d : %s \n",clien_id,buffer );
		for(int i=0;i<strlen(buffer);i++) buffer[i]=toupper(buffer[i]);
		printf("Server sending to client %d : %s \n",clien_id,buffer );	
		client_stream[clien_id].send_n(buffer,MAX_BUFFER_SIZE,0);	
	}
	client_stream[clien_id].close();
}

int main(int argc, char const *argv[])
{
	ACE_INET_Addr server("127.0.0.1:8080");
	ACE_INET_Addr client;
	ACE_SOCK_Acceptor client_acceptor(server);

	while(total_clients<MAX_CLIENTS)
	{
		int ret=client_acceptor.accept(client_stream[total_clients],&client);
		if(ret<0){printf("Error in accepting\n"); return 0;}
		printf("Connection accepted from %s:%d\n",client.get_host_name(),client.get_port_number() );
		cid[total_clients]=total_clients;
		ACE_Thread::spawn((ACE_THR_FUNC)serve,cid+total_clients);
		total_clients++;
	}
	ACE_Barrier barrier(total_clients);
	barrier.wait();
	return 0;
}