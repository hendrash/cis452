#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>

void handler(int signal);
void errorChecker();
int i, pid1, pid2, status;
int main(){
	int exit_status;
	errorChecker();
	pid1=getpid();
	printf("Parent pid =%d\n", pid1);
	if((pid2=fork())==0)
	{
		//child
		printf("Child pid = %d\n", getpid());

		printf("Child: sending parent SIGUSR1\n");
		kill(pid1, SIGUSR1);
		for(;;);
	}
	else{
		//parent
		wait(&status);
		if(WIFEXITED(status)){
			exit_status=WEXITSTATUS(status);
			if(exit_status>128)
			{
				exit_status-=256;
			}
			printf("Child return - %d\n", WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status))
		{
			printf("Child died on signal - %d\n", WTERMSIG(status));	
		}

	}
	return 0;
}
void errorChecker(){
	if(signal(SIGUSR1, handler)==SIG_ERR)
	{
		printf("Parent: Unable to create handler for SIGUSR1\n");
	}
	if(signal(SIGUSR2, handler)==SIG_ERR)
	{
		printf("Parent: Unable to create handler for SIGUSR2\n");
	}
	return;
}

void handler(int signal){
	switch(signal)
	{
		case SIGUSR1:
			printf("Process %d: received SIGUSR1 \n",getpid());
			if(pid1==getpid()) //parent
			{
				printf("Process %d is passing SIGUSR1 to %d ...\n",getpid(),pid2);
				kill(pid2, SIGUSR1);
			}
			else{ // child
				printf("Process %d is passing SIGUSR2 to itself ...\n",getpid());
				kill(getpid(), SIGUSR2);
			}	
			break;
		case SIGUSR2:
			printf("Process %d: received SIGUSR2 \n", getpid());
			if(pid1==getpid())//parent
			{
				printf("Process %d is passing SIGUSR2 to %d ..\n", getpid(), pid2);
				kill(pid2, SIGUSR2);
			}else{//child
				printf("Process %d will terminate itself using SIGINT\n",getpid());
				kill(getpid(), SIGINT);
				break;
			}
		default:
			break;
	}
	return;
}
