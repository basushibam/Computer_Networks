#include <stdio.h>          /* printf()                 */
#include <stdlib.h>         /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */

int main(int argc, char const *argv[])
{
	key_t Key=ftok(".",1234);
	int shmid=shmget(Key,sizeof(int), 0644 | IPC_CREAT),i,j=0,initial_value=1,l=1,status=0;
	int* p = (int *) shmat (shmid, NULL, 0);
	sem_t* sem = sem_open ("pSem", O_CREAT | O_EXCL, 0644,initial_value); 
	sem_unlink ("pSem");
	pid_t cpid,wpid;
	*p=5;
	for(i=1;i<=3;i++)
	{
		cpid=fork();
		if(cpid<0) printf("Error forking \n");
		else if(cpid==0) break;
		printf("Pid of Process %d = %d\n",i,cpid );
	}
	if(cpid!=0)
	{
		while (wait(&status) > 0);
		printf("All child processes have terminated \n");
		shmdt(p);
		shmctl (shmid, IPC_RMID, 0);
		//sem_destroy(sem);
		sem_close(sem);

	}
	else{
		printf("Child %d has started execution \n",i );
		while(j++<3)
		{
			sem_wait(sem);
			printf("Child %d has read value %d in iteration %d \n",i,*p,j);
			*p+=i;
			printf("Child %d has written value %d in iteration %d\n",i,*p,j);
			sem_post(sem);
			sleep(1);
		}
		printf("Child %d has finished execution.\n",i );
		exit(0);
	}
	return 0;
}