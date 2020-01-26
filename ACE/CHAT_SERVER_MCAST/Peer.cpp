#include <bits/stdc++.h>
#include <ace/Thread.h>
#include <ace/Synch.h>
#include <ace/streams.h>
#include <ace/INET_Addr.h>
#include <ace/SOCK_Dgram_Mcast.h>
#include <errno.h>
using namespace std;

ACE_SOCK_Dgram_Mcast mcast_dgram;
ACE_SOCK_Dgram dgram;

char nm[20];

void* receive(void* args)
{
	while(1)
	{
		ACE_INET_Addr remote_addr;
		char Message[100];
		mcast_dgram.recv (Message,100,remote_addr);
		printf("Message recieved from %s:%d \n",remote_addr.get_host_name(),remote_addr.get_port_number() );
		printf("%s\n",Message );
	}
}

void* sending(void* args)
{
	while(1)
	{
		char message[100]; char buffer[100]; buffer[0]=0;
		printf("Enter a message for the mcast group : \n");
		scanf("%s",message);
		printf("Sending message \n");
		strcat(buffer,nm); strcat(buffer," : "); strcat(buffer,message);
		ACE_INET_Addr remote_addr("127.0.0.1:8080");
		dgram.send(buffer,100,remote_addr);
		printf("Message sent to group \n");
	}
}

int main(int argc, char const *argv[])
{
	printf("Enter your name \n"); scanf("%s",nm);
	ACE_INET_Addr mcast_addr("127.0.0.1:8080");
	mcast_dgram.open(mcast_addr);
	
	printf("Subscribed to PORT %d \n",mcast_addr.get_port_number() );
	ACE_Thread::spawn((ACE_THR_FUNC)receive,NULL);
	ACE_Thread::spawn((ACE_THR_FUNC)sending,NULL);
	ACE_Barrier barrier(2); 
	printf("Client %s main thread is waiting \n", nm);
	barrier.wait();
	return 0;
}