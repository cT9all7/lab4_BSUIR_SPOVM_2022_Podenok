#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/signal.h>
#include<time.h>
#include<errno.h>
#include<stdbool.h>
#include<signal.h>
bool k;
bool k1=false;
int a[4];
struct ii
{
	int a,b;
};
struct ii tempst;
void handler (int signo)
{	
	if(signo == SIGUSR1) k=true;	
	if(signo==SIGUSR2) k=false;
	if(signo==SIGALRM)
	{
		k1=true;
		a[0]=tempst.a;
		a[1]=tempst.b;
	}
}
int main(int argc, char* argv[])
{
	int ret;
	if(signal(SIGUSR2,handler)==SIG_ERR) signal(SIGUSR2,SIG_IGN);
	if(signal(SIGUSR1,handler)==SIG_ERR) signal(SIGUSR1,SIG_IGN);
	if(signal(SIGALRM,handler)==SIG_ERR) signal(SIGALRM,SIG_IGN);
	for(int i=0;;i++)
	{
		ualarm(5000,0);
		for(int T=0;;T++)
		{
			if(k1==true)
			{
				k1=false;
				break;
			}
			if(T%2==0){
			tempst.a=0;
			tempst.b=0;
			}
			else{
			tempst.a=1;
			tempst.b=1;
			}
			a[2]=tempst.a;
			a[3]=tempst.b;
		}
		
		if(k==true && i%100==0)
		{
			printf("stat.| %d %d %d %d |",a[0],a[1],a[2],a[3]);	
			printf("parent| %d |", getppid());
			printf("child| %d | \n", getpid());
		}
	}
	return 0;
}