#include <bits/stdc++.h>          /* printf()                 */        /* exit(), malloc(), free() */
#include <unistd.h>
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>  
#include <pthread.h>
using namespace std;

int main()
{
	char buffer[100];
	char pipeForP4[] = "./pipeForP4";
	mkfifo(pipeForP4,0666);
	
	while(1){
		int fd = open(pipeForP4,O_RDONLY);
		if(fd<0){
			printf("Error in opening fifo in P4 \n"); exit(0);
		}
		int readcount = read(fd,buffer,100);
		if(readcount){
			printf("P4 read from AIS = %s \n",buffer );
		}
		else{
			printf("P4 read nothing \n");
		}
		close(fd);
	}
	
}