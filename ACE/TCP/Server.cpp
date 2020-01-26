#include <bits/stdc++.h>
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/INET_Addr.h"
using namespace std;

int main(int argc, char const *argv[])
{
	ACE_INET_Addr server(8080);
	ACE_SOCK_Acceptor client_acceptor(server);
	ACE_SOCK_Stream client_stream;
	
	ACE_INET_Addr client; 
	printf("Trying to accept client request \n");
	if (-1 == client_acceptor.accept(client_stream, &client)) { 
		    printf("Connection not established with client!\n");
		    return 0;
		} else { 
		    printf("Client details: Host Name: %s Port Number: %d\n", 
		         client.get_host_name(), client.get_port_number());
		}
	while(1)
	{
		char buffer[100];
		if (-1 == client_stream.recv_n(buffer, 100, 0)) { 
		   printf("Error in reading client data!\n");   
		   return 0;
		} else { 
		   printf("Client message: %s\n", buffer);
		}
		for(int i=0;i<strlen(buffer);i++) buffer[i]=toupper(buffer[i]);
		client_stream.send_n(buffer,100,0);
	}
	client_stream.close();
	return 0;
}