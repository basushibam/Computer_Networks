#include<bits/stdc++.h>
#include<stdio.h>
#include<cstring>
#include<string>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include<cstdlib>
#include<unistd.h>
#include<pthread.h>
using namespace std;

string currentProcess;
sem_t* sem;
void* reading(void* args)
{
	string cp="./"+currentProcess;
	while(1)
	{
		int rfd=open(cp.c_str(),O_RDONLY);
		char input[100];
		read(rfd,input,100);
		string inp(input);
		if(inp.length()>0)
		cout<<"Message read by "<<currentProcess<<" = "<<inp<<endl;
		close(rfd);
	}
}

void* writing(void* args)
{
	char fifoname[]="./mainFIFO";
	
	while(1)
	{
		string output;
		
		int wfd=open(fifoname,O_WRONLY);
		cout<<"Process "<<currentProcess<<" wants to send data "<<endl;
		cin>>output;
		cout<<currentProcess<<" wants to send data = "<<output<<endl;
		string temp=currentProcess; temp+=" MSG "+output;
		cout<<"Data being sent = "<<temp<<endl;
		write(wfd,temp.c_str(),100);

		close(wfd);
	}
}
int main(int argc, char const *argv[])
{
	pid_t cpid=getpid();
	char fifoname[]="./mainFIFO";
	string output;
	cout<<"Enter the name of the currentProcess "<<endl;
	cin>>currentProcess;
	//Request for opening local pipe 
		cout<<currentProcess<<" wants to send join request "<<endl;
		
		

		cin>>output;
		string temp=currentProcess; temp+=" "; output=temp+output;
		cout<<"Output = "<<output<<endl;
		
		int wfd=open(fifoname,O_WRONLY);
		write(wfd,output.c_str(),100);
		close(wfd);
	
	

	pthread_t reader,writer;
	pthread_create(&reader,NULL,reading,NULL);
	pthread_create(&writer,NULL,writing,NULL);
	pthread_join(reader,NULL);
	pthread_join(writer,NULL);
	return 0;
}