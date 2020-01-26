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
	FILE* fp=popen("./p3","w");
	int fd=fileno(fp);
	string s;
	cin>>s;
	cout<<"Programm p2 gets input = "<<s<<endl;
	write(fd,s.c_str(),strlen(s.c_str()));
	cout<<"Programm p2 outputs it to p3"<<endl;
}