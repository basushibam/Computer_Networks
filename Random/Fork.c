#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int c=0;
	pid_t cpid;
	printf("In the beginning of parent process \n" );
	char *fp[]={"./MAIN",NULL};
	c=fork();
	if(c>0)
	{
		printf("Inside if condition of parent process \n");
	}
	else 
	{
		execvp(fp[0],fp);
		printf("Inside else condition of child process \n");
	}
	wait(NULL);
	printf("In the end of the parent process \n");
	return 0;
}