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
}
printf("\nspawned child PID# %i\n", pid);
signal(SIGINT,sigHandler);
pause();

}

void sigHandler(int sigNum){
	sleep(1);
	printf("\nAll processes ending\n");
	exit(0);
}
