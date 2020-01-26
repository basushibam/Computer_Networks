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

int main(int argc, char const *argv[])
{
	pid_t cpid;
	
	sem_t* sem=sem_open("s_sem",O_CREAT,0664,0);
	int pfd=open("./text.txt",O_RDONLY),ret;
	dup2(pfd,0);
	cpid=fork();
	if(cpid>0)
	{
		for(int i=0;i<10;i++)
	{
		string str;
		getline(cin,str);
		cout<<str<<endl;
	}
	sem_post(sem);
	}
	else
	{
		execvp("./dup2_test2",NULL);
	}
	


}