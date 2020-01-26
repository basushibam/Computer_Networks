#include<bits/stdc++.h>
#include<semaphore.h>
#include<sys/types.h>
#include<unistd.h>
using namespace std;

int x,y;
sem_t s1,s2;

void* p1(void *arg)
{
	while(1)
	{
		printf("Inside p1()\n");
		sleep(1);
		sem_wait(&s1);
		printf("x = %d and y = %d\n",x,y);
		y=x+1;
		sem_post(&s2);
		printf("After performing y=x+1 are x=%d and y=%d\n",x,y);
	}
}

void* p2(void *arg)
{
	while(1)
	{
		printf("Inside p2()\n");
		sleep(1);
		sem_wait(&s2);
		printf("x = %d and y = %d\n",x,y);
		x=y+1;
		sem_post(&s1);
		printf("After performing x=y+1 are x=%d and y=%d\n",x,y);
	}
}
int main()
{
	sem_init(&s1,0,1); sem_init(&s2,0,0);
	x=5; y=3;
	pthread_t t1,t2;
	pthread_create(&t1,NULL,p1,NULL);
	pthread_create(&t2,NULL,p2,NULL);
	pthread_join(t1,NULL); pthread_join(t2,NULL);
	return 0;
}