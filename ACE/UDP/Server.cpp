#include <bits/stdc++.h>
#include <ace/OS.h>
#include <ace/SOCK_Dgram.h>
#include <ace/INET_Addr.h>
using namespace std;

#define MYPORT 8080

int main(int argc, char const *argv[])
{
	ACE_INET_Addr server(MYPORT);
	ACE_SOCK_Dgram server_data(server);
	ACE_INET_Addr client;
	//ACE_INET_Addr client("127.0.0.1", 9000);
	char message[100]; 
	printf("Receiving message \n");
	size_t sent_data_length = server_data.recv(message,100,client);
	if (sent_data_length == -1)  printf("Error in data transmission\n");
	printf("Message recieved form %s \n",client.get_host_name());
	printf("Message received : %s \n",message );
	server_data.send("Got Your Message",100,client);
	server_data.close();

	return 0;
}