#include <bits/stdc++.h>
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/INET_Addr.h"
using namespace std;

int main(int argc, char const *argv[])
{
	ACE_INET_Addr server(8080, "127.0.0.1");
	ACE_SOCK_Stream client_stream; 
	ACE_SOCK_Connector client_connector;
	printf("Trying to connect with server \n");
	if (-1 == client_connector.connect(client_stream, server)) { 
	  printf ("Failure to establish connection!\n");
	  return 0;
	}
	while(1)
	{
		char message[100];
		printf("Enter a message : "); scanf("%s",message);
		client_stream.send_n(message, 100, 0); 
		if (-1 == client_stream.recv_n(message, 100, 0)) { 
		   printf("Error in reading server data!\n");   
		   return 0;
		} else { 
		   printf("Server message: %s\n", message);
		}
	}
	 
	client_stream.close( ); // close when done
	return 0;
}