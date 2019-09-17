#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>

void handler(int signal);
void errorChecker();
int i, pid1, pid2, status;
int main(){
	// Installing signal handlers 
	if(signal(SIGUSR1, handler)==SIG_ERR){
		printf("Unable to install a signal handler for SIGUSR1\n");
	}
	if(signal(SIGUSR2, handler)==SIG_ERR){
		printf("Unable to install a signal handler for SIGUSR2\n");
	}
	pid1=getpid();
	printf("Parent pid=%d\n", pid1);
	if(pid2=fork()==0)//child
	{
		printf("Child pid =%d\n", pid1);

		printf("Child: sending parent SIGUSR1 ..........");
		kill(pid1, SIGUSR1);

		printf("Child: sending parent SIGUSR2 ..........");
		kill(pid1, SIGUSR2);
		wait( &status);
		printf("Child: sending parent SIGUSR2 ..........");
		kill(pid1, SIGUSR2);
	}
	else{//parent
		wait(&status);
		for(;;);
	}
}

void handler(int signo){
	if(signo==SIGUSR1){
		printf("received a SIGUSR1 signal %d \n", signo);

		//Reinstalling handlers 
		if(signal(SIGUSR1, handler)==SIG_ERR)
			printf("Unable to install a signal handler for SIGUSR1\n");
}

	if(signo==SIGUSR2){
		printf("received a SIGUSR2 signal %d \n", signo);} 
	//Reinstalling handlers 
	if(signal(SIGUSR2, handler)==SIG_ERR)
		printf("Unable to install a signal handler for SIGUSR2\n");


	return;
}





