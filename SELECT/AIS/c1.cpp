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

#define LOOPS 5

int main(int argc, char const *argv[])
{
	

	int fd2 = open("./client1",O_WRONLY);
	printf("FD2 of client 1 = %d \n",fd2);
	int l = 0;
	char buffer[100];
	//int fd = open("./f2.txt",O_RDONLY);
	int fd = 0;
	while(1){
		fd2 = open("./client1",O_WRONLY);
		
		read(fd,buffer,100);

		write(fd2,buffer,100);
		printf("Value written in fifo by client 1 = %s\n",buffer );
		sleep(5);
		
		close(fd2);
	}
	close(fd);
	return 0;
}