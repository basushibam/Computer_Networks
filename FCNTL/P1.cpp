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

int main(int argc, char const *argv[])
{
	FILE* fp = fopen("text.txt","r");
	int fd = fileno(fp);
	int nfd=fcntl(fd, F_DUPFD, 0);
	int linesRead=0;
	while(linesRead<2)
	{
		char c;
		int ret = read(fd,&c,1);
		if(ret<=0)
		{
			printf("Error in reading file \n");
		}
		else
		{
			printf("%c",c ); if(c=='\n') linesRead++;
		}
		
	}
	pid_t cpid = fork();
	if(cpid==0)
	{
		linesRead=0;
		while(linesRead<2)
		{
		char c;
		int ret = read(nfd,&c,1);
		if(ret<=0)
		{
			printf("Error in reading file \n");
		}
		else
		{
			printf("%c",c ); if(c=='\n') linesRead++;
		}
		
		}

	}
	return 0;
}