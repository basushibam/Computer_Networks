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

#define MAX_BUFFER_SIZE 100
char message[MAX_BUFFER_SIZE];
int main(int argc, char const *argv[])
{
	ACE_INET_Addr server("127.0.0.1:8080");
	ACE_SOCK_Stream client_stream;
	ACE_SOCK_Connector client_connector;

	printf("Trying to connect with server \n");
	if (-1 == client_connector.connect(client_stream, server)) { 
	  printf ("Failure to establish connection!\n");
	  return 0;
	}
	while(1)
	{
		
		printf("Enter a message : "); scanf("%s",message);
		client_stream.send_n(message, MAX_BUFFER_SIZE, 0); 
		if (-1 == client_stream.recv_n(message, MAX_BUFFER_SIZE, 0)) { 
		   printf("Error in reading server data!\n");   
		   return 0;
		} else { 
		   printf("Server message: %s\n", message);
		}
	}
	 
	client_stream.close( ); 
	return 0;
}