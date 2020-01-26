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

string s,currentProcess;
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
		cout<<inp<<endl;
		close(rfd);
	}
}

void* writing(void* args)
{
	char fifoname[]="./mainFIFO";
	string output;
	while(1)
	{
		int wfd=open(fifoname,O_WRONLY);
		//sem_wait(sem);
		cout<<"Process "<<s<<" wants to send data "<<endl;
		cin>>output;
		string temp=currentProcess; temp+=" "; output=temp+output;
		write(wfd,output.c_str(),100);
		//sem_post(sem);
		close(wfd);
	}
}
int main(int argc, char const *argv[])
{
	int cfd; 
	stringstream ss;
	char cpipe[100]; pid_t cpid=getpid();
	
	char fifoname[]="./mainFIFO";
	sem=sem_open("s_sem",0);
	cfd=open(fifoname,O_WRONLY);
	printf("Enter the name of current process \n"); cin>>currentProcess;
	s=currentProcess;
	printf("%s wants to send pipe name '%s' to Server Program \n",currentProcess.c_str(),s.c_str() );
	cout<<"Writing value = "<<s<<endl;
	write(cfd,s.c_str(),100);
	//sem_post(sem);
	pthread_t reader,writer;
	pthread_create(&reader,NULL,reading,NULL);
	pthread_create(&writer,NULL,writing,NULL);
	pthread_join(reader,NULL);
	pthread_join(writer,NULL);
	return 0;
}