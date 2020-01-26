#include<bits/stdc++.h>
#include<stdio.h>
#include<cstring>
#include<string>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include<cstdlib>
#include<unistd.h>
#include<poll.h>
#include<pthread.h>
using namespace std;


int c;
string pipe12= "./xyread";
string pipe22 = "./xywrite";

static void signalHandler(int sig){
	int fd1 = open(pipe22.c_str(),O_RDONLY);
	char buffer[100];
	read(fd1,buffer,100);
	close(fd1);
	string XY(buffer);
	cout<<"Value read = "<<XY<<endl;
	stringstream xy; xy<<XY;
	int x,y; xy>>x>>y;
	y = x+1;
	string X = to_string(x); string Y = to_string(y);
	XY=X+" "+Y;
	kill(c,SIGUSR1);
	int fd2 = open(pipe12.c_str(),O_WRONLY);
	write(fd2,XY.c_str(),100);
	close(fd2);
	
	sleep(2);
}
int main(int argc, char const *argv[])
{
	signal(SIGUSR2,signalHandler);
	mkfifo(pipe12.c_str(),0666);
	mkfifo(pipe22.c_str(),0666);
	c=fork();
	if(c>0)
	{
		while(1);
	}
	else
	{
		execvp("./test2",NULL);
	}
	return 0;
}