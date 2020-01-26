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

int main(int argc, char const *argv[])
{
	char pipeName[]="./pipe3";
	int i=0;
	int fd = open(pipeName,O_WRONLY);
	
	
	cout<<"Inside client 3"<<endl;
	char buffer[100]="Inside client 3 buffer ";
	while(i++<2)
	{
		cout<<"Hello 3"<<endl;	
		
		write(fd,buffer,100); sleep((rand()%100)/50.0);
		
	}
	close(fd);
	return 0;
}