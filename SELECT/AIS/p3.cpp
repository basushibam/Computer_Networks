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

#define LOOPS 20

int main(int argc, char const *argv[])
{
	int i=0,processToBeSignalled = 0;
	printf("Enter the PID of the AIS process to be signalled \n");
	scanf("%d",&processToBeSignalled);
	char ch = 'n';
	while(1) {
		printf("Signal ?\n");
		scanf("%c",&ch);
		if(ch=='y'){
			printf("P3 signalled AIS \n");
		kill(processToBeSignalled,SIGUSR1);
		}
	}
	return 0;
}