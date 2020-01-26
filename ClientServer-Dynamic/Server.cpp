#include <bits/stdc++.h>          /* printf()                 */        /* exit(), malloc(), free() */
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


vector<string> pipes;


int main(int argc, char const *argv[])
{
	int ret,sfd,n=3,rfd;
	char fifoname[]="./mainFIFO";
	ret=mkfifo(fifoname,0666);
	if(ret<0)
	{
		printf("Error in creating named pipe 'mainFIFO' .\n");
		exit(0);
	}
	
	while(1)
	{
		cout<<"Waiting for client request "<<endl;
		rfd = open(fifoname,O_RDONLY);
		char input[100]; string clientname,instruction;
		read(rfd,input,100);
		string inp(input),pipename;
		string inp2=inp;
		cout<<"Value read = "<<inp<<endl;
		stringstream ss;
		ss<<inp; ss>>clientname; ss>>instruction;
		pipename="./"+clientname;
		if(instruction=="JOIN")
		{
			pipes.push_back(pipename);
			ret = mkfifo(pipename.c_str(),0666);
			cout<<"Pipe created for "<<clientname<<endl;
			if(ret<0)
			{	
				printf("Error in creating named pipe %s for Process %s .\n",pipename.c_str(),clientname.c_str());
				exit(0);
			}
		}	
		else if(instruction == "MSG")
		{
			string message = inp2;
			for(int i=0;i<pipes.size();i++)
			{
				if(pipes[i]!=pipename)
				{
					cout<<"Broadcasting message "<<inp<<" to user "<<pipes[i]<<endl;
					int wfd=open(pipes[i].c_str(),O_WRONLY);
					write(wfd,inp2.c_str(),100);
					close(wfd);
				}
			}
		}
		else
		{
			cout<<"WRONG INSTRUCTION BY CLIENT "<<clientname<<endl;
		}
		close(rfd);

	}
	return 0;
}