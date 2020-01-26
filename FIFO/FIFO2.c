#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include<sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h> 

int main(int argc, char const *argv[])
{
	int ret,value,initial_value=0;
	FILE* fp;
	char fifoname[]="./main";
	printf("Inside program FIFO2.Going to open file 'main' \n");
	fp=fopen(fifoname,"r");
	if(fp==NULL) 
	{
		printf("Error in opening the pipe by parent \n"); 
		exit(0);
	}	 
	//sem_t* sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644,initial_value); 
	//sem_t* sem = sem_open("pSem",0);
	//sem_unlink ("pSem");
	//sem_wait(sem);
	printf("Hello\n");
	ret=fscanf(fp,"%d",&value);
	printf("Value read by FIFO2 process = %d \n",value );
	//sem_close(sem);
	fflush(fp);
	//unlink(fifoname);
	exit(0);
	return 0;
}