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
#include<pthread.h>
using namespace std;


int p;
string pipe22 = "./xyread";
string pipe12 = "./xywrite";

static void signalHadler(int sig){
	int fd2 = open(pipe22.c_str(),O_RDONLY);
	char buffer[100];
	read(fd2,buffer,100);
	close(fd2);
	string XY(buffer);
	cout<<"Value read = "<<XY<<endl;
	stringstream xy; xy<<XY;
	int x,y; xy>>x>>y;
	x = y+1;
	string X = to_string(x); string Y = to_string(y);
	XY=X+" "+Y;
	kill(p,SIGUSR2);
	int fd1 = open(pipe12.c_str(),O_WRONLY);
	write(fd1,XY.c_str(),100);
	close(fd1);
	
	sleep(2);
} 

int main(int argc, char const *argv[])
{
	printf("Inside process 2 \n");
	signal(SIGUSR1,signalHadler);
	p = getppid();
	string s = "1 0";
	kill(p,SIGUSR2);
	int fd = open(pipe12.c_str(),O_WRONLY);
	write(fd,s.c_str(),100);
	close(fd);
	while(1);
	return 0;
}