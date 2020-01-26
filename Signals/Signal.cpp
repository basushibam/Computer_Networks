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

int p2pid;

static void read1(int sig)
{
	char fifoname1[]="./p1Sender";
	char fifoname2[]="./p2Sender";
	char ppid[10]; 
	int rfd=open(fifoname2,O_RDONLY);
	read(rfd,ppid,10);
	close(rfd);
	string temp(ppid);
	cout<<"PID of process P2 read by P1 = "<<temp<<endl;
	p2pid=atoi(ppid);
	string s;
	int linesRead=0;
	while(linesRead<2)
	{
		char c; scanf("%c",&c);
		cout<<c; if(c=='\n') linesRead++;
	}
		int pid=getpid(); 
		stringstream ss; ss<<pid; ss>>s;
		
		int wfd=open(fifoname1,O_WRONLY);
		write(wfd,s.c_str(),10);
		close(wfd);
		//signal(SIGUSR2,read1);
		kill(p2pid,SIGUSR1);
}

int main()
{
	signal(SIGUSR2,read1);
	char fifoname1[]="./p1Sender";
	char fifoname2[]="./p2Sender";
	int ret = mkfifo(fifoname1,0666);
	ret = mkfifo(fifoname2,0666);
	if(ret<0)
	{
		cout<<"Error in creating pipe in process P1 "<<endl; exit(0);
	}
	cout<<"Pipe pidSender created in Process P1"<<endl;
	FILE* fp = fopen("text.txt","r");
	int fd = fileno(fp);
	dup2(fd,0);
	pid_t cpid = fork();
	if(cpid==0)  //child program
	{
		
		cout<<"Inside  child process "<<endl;
		cout<<"Performing execvp to P2 "<<endl;
		execvp("./P2",NULL);
	}
	else
	{
		int parentPid = getpid(); 
		string pid;
		stringstream ss; ss<<parentPid; ss>>pid;
		cout<<"PID of process P1 in integer = "<<parentPid<<endl;
		cout<<"PID of process P1 in string = "<<pid<<endl;
		int wfd=open(fifoname1,O_WRONLY);
		write(wfd,pid.c_str(),10);
		close(wfd);
		while(cin)
		{
			cout<<"P1 is Waiting for signal "<<endl;
		}
	}
}