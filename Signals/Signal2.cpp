#include <bits/stdc++.h>         
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include<sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>  
#include <pthread.h>
using namespace std;

int p1pid;

static void read2(int sig)
{
	char fifoname1[]="./p1Sender";
	char fifoname2[]="./p2Sender";
	string s;
	int linesRead=0;
	while(linesRead<2)
	{
		if(cin)
		{
			getline(cin,s);
			cout<<"Line = "<<s<<endl;
			linesRead++;
		}
		else break;
	}
		int pid=getpid();
		stringstream ss; ss<<pid; ss>>s;
		int wfd=open(fifoname2,O_WRONLY);
		write(wfd,s.c_str(),10);
		close(wfd);
		//signal(SIGUSR1,read2);
		kill(p1pid,SIGUSR2);
}

int main()
{
	cout<<"Process p2 has started executing "<<endl;
	signal(SIGUSR1,read2);
	char fifoname1[]="./p1Sender";
	char fifoname2[]="./p2Sender";
	char ppid[10]; 
	int rfd=open(fifoname1,O_RDONLY);
	read(rfd,ppid,10);
	close(rfd);
	string s(ppid);
	cout<<"PID of P1 read = "<<s<<endl;
	p1pid=atoi(ppid);
	cout<<"p1pid = "<<p1pid<<endl;


	int pid=getpid();
		stringstream ss; ss<<pid; ss>>s;
		int wfd=open(fifoname2,O_WRONLY);
		write(wfd,s.c_str(),10);
		close(wfd);
	kill(p1pid,SIGUSR2);
	while(cin)
		{
			cout<<"P2 is Waiting for signal "<<endl;
		}
	
}