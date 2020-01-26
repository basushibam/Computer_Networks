#include <bits/stdc++.h>
#include <ace/OS.h>
#include <ace/SOCK_Dgram.h>
#include <ace/INET_Addr.h>
using namespace std;

#define SERVPORT 8080

int main(int argc, char const *argv[])
{
	
	ACE_INET_Addr server(SERVPORT,"127.0.0.1");
	ACE_INET_Addr client(9000);
	ACE_SOCK_Dgram client_data(client);
	
	char message[100];
	printf("Enter a message \n"); scanf("%s",message);
	size_t sent_data_length = client_data.send(message, 100, server);
	if (sent_data_length == -1) 
	  printf("Error in data transmission\n");
	client_data.recv(message,100,server);
	printf("Client received : %s \n",message ); 
	client_data.close();
	return 0;
}