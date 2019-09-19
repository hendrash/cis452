#define _POSIX_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
void handler(int signal);
void errorChecker();
void quit();
int i, pid1, pid2, status;
int main(){
	int sig, slp;
	pid1=getpid();
	printf("Parent pid=%d\n", pid1);
	if((pid2=fork())==0)//child
	{
		printf("Child pid =%d\n", pid2);
	while(1){	
		sig=rand() % 2;
		slp=rand()%5+1;	
			
		if(sig==1){
		printf("Child: sending parent SIGUSR1 ..........");
		fflush(stdout);
		kill(pid1, SIGUSR1);
		sleep(slp);	
		}
		else{
		printf("Child: sending parent SIGUSR2 ..........");
		fflush(stdout);
		kill(pid1, SIGUSR2);
		sleep(slp);
		}
	}
	
	}
	else{
		if(signal(SIGINT, quit)==SIG_ERR){
		printf("Unable to install a signal hander for SIGINT\n");		
		}
		// Installing signal handlers 
	if(signal(SIGUSR1, handler)==SIG_ERR){
		printf("Unable to install a signal handler for SIGUSR1\n");
	}
	if(signal(SIGUSR2, handler)==SIG_ERR){
		printf("Unable to install a signal handler for SIGUSR2\n");
	}
	
		//parent 
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

void quit(){
if(pid1==getpid()){
//parent;
printf("\nending program .... \n");
exit(0);
}
else{
fflush(stdout);
	printf("...");	
sleep(1);
exit(0);
}
}





