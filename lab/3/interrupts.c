#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
void sigHandler(int);

int main(){

pid_t pid;

if((pid=fork()) < 0){
	perror("forking error");
} else if (pid) { //parent's code
	printf("\nspawned child PID# %i\n", pid);
	signal(SIGINT,sigHandler);
	signal(SIGUSR1, sigHandler);
	signal(SIGUSR2, sigHandler);
	printf("waiting...");
	sleep();
} else { //child's code

	while(1) {
		//sleep for 1-5 random seconds
		//int randomTime = rand() %5 + 1;
		//sleep(randomTime);
		
		//TODO generate signals
	}
	
}


}

void sigHandler(int sigNum){
	
	if(sigNum == 2) {
		sleep(1);
		printf("\nAll processes ending\n");
		exit(0);
	} else if (sigNum == 10) {
		printf("received a SIGUSR1 signal")
	} else if (sigNum == 12) {
		printf("received a SIGUSR2 signal")
	}
}
