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
printf("Parent pid=%d\n ", pid1);
if(pid2=fork()==0)
{
	printf("Child pid =%d\n", pid1);
	printf("Child: sending parent SIGUSR1");
	kill(pid1, SIGUSR1);
	printf("Child: sending parent SIGUSR2");
	kill(pid1, SIGUSR2);
}
else{

	wait(&status);
}
}

void handler(int signal){
if(signal==SIGUSR1){
printf("siguser1 hihhihihihh\n");
}
if(signal==SIGUSR2)
printf("siguser2 lololoololololol\n");
}
