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

int main()
{
	FILE* fp = fopen("text.txt","r");
	int fd = fileno(fp);
	sem_t* sem=sem_open("s_sem",O_CREAT,0664,0);
	dup2(fd,0);
	pid_t cpid;
	cout<<"Creating child process -------------------------------"<<endl;
	cpid=fork();
	if(cpid>0)
	{
		int cnt=0;
		while(cnt<2)
		{
			char ch;
			scanf("%c",&ch);
			printf("%c",ch );
			if(ch=='\n') cnt++;
		}
	sem_post(sem);
	}
	else
	{
		execvp("./dup22",NULL);
	}
}
