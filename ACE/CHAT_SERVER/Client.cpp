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

ACE_SOCK_Stream cli_stream;
char nm[20];

void *receive(void *arg)
{
	while(1)
	{
		char ans[100];
		cli_stream.recv_n(ans,100,0);
		printf("%s\n",ans );
	}
}

void *sending(void *arg)
{
	while(1)
	{
		char buf[100],ans[100];
		printf("Enter a message for the group : \n"); scanf("%s",buf);
		ans[0]=0; strcat(ans,nm); strcat(ans," : "); strcat(ans,buf);
		cli_stream.send_n(ans,100,0);
	}
}

int main()
{
	ACE_INET_Addr server(3000,"127.0.0.1");
	ACE_SOCK_Connector connection_obj;
	printf("Enter your name \n"); scanf("%s",nm);
	connection_obj.connect(cli_stream,server);
	perror("connect ");
	ACE_Thread::spawn((ACE_THR_FUNC)sending,NULL);
	ACE_Thread::spawn((ACE_THR_FUNC)receive,NULL);
	ACE_Barrier barrier(2);
	printf("Client Main Thread is waiting \n");
	barrier.wait();
	return 0;
}