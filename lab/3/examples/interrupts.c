#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>
#include<string.h>
#define READ 0
#define WRITE 1
#define MAX 1024

void sigHandler(int);

void parent();
void child();
char *str ="hello world\n";	
pid_t pid;

int main(){

	if((pid=fork()) < 0){
		perror("forking error");
	} else if (pid) { //parent's code
		parent();
}else{
child();
}
}
void sigHandler(int sig){
printf("hello world");
	/*	if(sig==SIGUSR1){
write(STDIN_FILENO,"received a SIGUSER1 signal. signal Id:", 10);
	
	}
	if(sig==SIGUSR2){
	printf("received a SIGUSER2 signal signal Id: %d \n", sig);
	}*/
}

void quit(int sigNum){
	
	if(sigNum == 2) {
		sleep(1);
		printf("\nAll processes ending\n");
		exit(0);
	} else if (sigNum == 10) {
		printf("received a SIGUSR1 signal");
	} else if (sigNum == 12) {
		printf("received a SIGUSR2 signal");
	}
}








void parent(){
	kill(pid,SIGINT);
}

void child(){
	signal(SIGINT, sigHandler);
}
