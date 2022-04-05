#include<stdio.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/wait.h>
bool ok=true;
bool okin;
char a;
char a1;
int i=0;
pid_t mpid[99];
void handler(int signo)
{
	int ret;
	if(signo==SIGALRM)
	{ 
		printf("\n\n\n\n");
		if(okin==true) ok=true;
		if(okin==false)
		{
			ok=true;
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGUSR1);
				if(ret) perror("kill");
			}
		}
	}
}
int main(int argc, char* argv[])
{
	pid_t pid;
	int temp;
	int stat;
	int ret;
	int inputpid;
	for(int T=0;;T++)
	{		
		if(signal(SIGALRM,handler)==SIG_ERR) signal(SIGALRM,SIG_IGN);
		a=getchar();
		if(a=='p')
		{
			ok=false;
			okin=false;
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGUSR2);
				if(ret) perror("kill");
			}
			printf("input pid process\n");
			scanf("%d",&inputpid);
			for(int j=0;j<i;j++)
			{
				if(inputpid==mpid[j])
				{
					ret=kill(mpid[j],SIGUSR1);
					if(ret) perror("kill");
				}
			}
			alarm(5);
		}	
		else if(a=='+')
		{
			printf("**********PROCESS CHILD №  *********** \n");
			pid=fork();
			if(pid>0)
			{
				mpid[i]=pid;
				printf("%d == %d\n", mpid[i],pid);
			}
			if(!pid) ret=execve("/home/kali/progi/lab02/child(полный путь к вашему исполняемому child)",NULL,NULL);
			i++;
			temp=i;
		}
		else if(a=='-')
		{
			temp--;
			printf("KILL_PID==:%d\n",mpid[temp]);
			ret=kill(mpid[temp],SIGKILL);
			if(ret) perror("kill");
			pid=waitpid(mpid[temp],&stat,0);
			if(pid==-1) perror("waitpid");
			else if(WIFSIGNALED(stat)) printf("process %d killed, signal==%d \n",mpid[temp],WTERMSIG(stat));
			i--;
		}
		else if(a=='k')
		{
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGKILL);
				if(ret) perror("kill");
				pid=waitpid(mpid[j],&stat,0);
				if(pid==-1) perror("waitpid");
				else if(WIFSIGNALED(stat)) printf("process %d killed, signal==%d \n",mpid[j],WTERMSIG(stat));
			}
			i=0;			
		}
		else if(a=='g' && ok==true)
		{
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGUSR1);
				if(ret) perror("kill");
			}
		}
		else if(a=='g' && ok==false)
		{
			okin=true;
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGUSR2);
				if(ret) perror("kill");
			}
		}
		else if(a=='G')
		{
			printf("\ninput pid process\n");
			scanf("%d",&inputpid);
			for(int j=0;j<i;j++)
			{
				if(mpid[j]==inputpid)
				{
					ret=kill(mpid[j],SIGUSR1);
					if(ret) perror("kill");
				}
			}
		}
		else if(a=='S')
		{
			printf("\ninput pid process\n");
			scanf("%d",&inputpid);
			for(int j=0;j<i;j++)
			{
				if(mpid[j]==inputpid)
				{
					ret=kill(mpid[j],SIGUSR2);
					if(ret) perror("kill");
				}
			}
		}
		else if(a=='s')
		{
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGUSR2);
				if(ret) perror("kill");
			}
		}
		else if(a=='q')
		{
			for(int j=0;j<i;j++)
			{
				ret=kill(mpid[j],SIGKILL);
				if(ret) perror("kill");
				pid=waitpid(mpid[j],&stat,0);
				if(pid==-1) perror("waitpid");
				else if(WIFSIGNALED(stat)) printf("process %d killed, signal==%d \n",mpid[j],WTERMSIG(stat));
			}
			i=0;
			return 0;
		}
	}
	return 0;
}
