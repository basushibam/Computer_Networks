#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include<sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */

int main()
{
	int ret,status=0,value,initial_value=0;
	FILE *pfp;
	pid_t cpid;
	char fifoname[]="./main"; char *fp[]={"./FIFO2",NULL};
	//sem_t* sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644,initial_value); 
	//sem_unlink ("pSem");
	ret = mknod(fifoname, S_IFIFO | 0600, 0);
	if(ret<0)
	{
		printf("Error in creating named pipe 'main' .\n");
		exit(0);
	}
	cpid = fork();
	if(cpid<0){
		printf("Error in forking \n"); exit(0);
	}
	if(cpid>0)
	{

		pfp = fopen(fifoname,"w");
		if(pfp==NULL) 
		{
			printf("Error in opening the pipe by child \n"); exit(0); 
		}

		fprintf(pfp, "%d",1000 );
		printf("Parent process has written 1000 \n");
		//sem_post(sem);
		printf("Parent process has Singalled FIFO2\n");
		sleep(1);
		
		//sem_close(sem);
		fflush(pfp);
	}
	else
	{
		printf("Inside child process. Going to perform exec to program FIFO2 \n");
		execvp(fp[0],fp);
	}
}