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
	sem_t* sem=sem_open("s_sem",0);
	sem_wait(sem);
	cout<<"Reading in program dup22 ---------------------------"<<endl;
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
