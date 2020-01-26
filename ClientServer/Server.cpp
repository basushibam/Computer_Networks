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
	int ret,sfd,n=3;
	
	sem_t* sem=sem_open("s_sem",O_CREAT,0664,1);
	char fifoname[]="./mainFIFO";
	ret=mkfifo(fifoname,0666);
	if(ret<0)
	{
		printf("Error in creating named pipe 'mainFIFO' .\n");
		exit(0);
	}
	
	for(int i=0;i<n;i++)
	{
		sfd = open(fifoname,O_RDONLY);
		char cpipe[100]; string pipename,clientname;
		stringstream ss;
		//sem_wait(sem);
		read(sfd,cpipe,100);
		cout<<"Value read = "<<cpipe<<endl;
		string s(cpipe);
		clientname=s; pipename=s;
		pipename="./"+pipename;
		pipes.push_back(pipename);
		printf("Process %s wants a pipe named %s \n",clientname.c_str(),pipename.c_str());
		ret = mknod(pipename.c_str(), S_IFIFO | 0600, 0);
		if(ret<0)
		{
			printf("Error in creating named pipe %s for Process %s .\n",pipename.c_str(),clientname.c_str());
			exit(0);
		}
		int fd =open(pipename.c_str(),O_WRONLY);
		cout<<"Pipe created for "<<s<<endl;
		//sem_post(sem);
		close(fd);
		close(sfd);
	}
	cout<<"Now server will listen to the main pipe"<<endl;
	while(1)
	{
		char input[100];
		string user;
		int rfd=open(fifoname,O_RDONLY);

		read(rfd,input,100);
		string inp(input);
		string inp2=inp;
		cout<<"Server has read string "<<inp<<" and is processing the message "<<endl;
		stringstream sss; sss<<inp;
		sss>>user;
		user="./"+user;
		for(int i=0;i<pipes.size();i++)
		{
			cout<<"Iterating in user "<<pipes[i]<<endl;

			if(pipes[i]!=user)
			{
				cout<<"Broadcasting message "<<inp<<" to user "<<pipes[i]<<endl;
				int wfd=open(pipes[i].c_str(),O_WRONLY);
				write(wfd,inp2.c_str(),100);
				close(wfd);
			}
		}
		close(rfd);

	}
	close(sfd);


	return 0;
}