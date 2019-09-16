#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>
#define READ 0
#define WRITE 1
#define MAX 1024
void parent(int *);
void child(int *);

	char str[MAX];
int main()
{
	int fd[2];
	ssize_t num;
	pid_t pid;

	if (pipe (fd) < 0) {
		perror ("plumbing problem");
		exit(1);
	}
	// point A

	if ((pid = fork()) < 0) {
		perror ("fork failed");
		exit(1);
	}
	// point B

	else if (pid) {
		child(fd);
	}
	else{
		parent(fd);	
}
	return 0;
}

void parent(int * pipe){
		// Parent
		dup2 (pipe[WRITE], STDOUT_FILENO);
		// point C
		close (pipe[READ]);
		close (pipe[WRITE]);
		// point D
		strcpy(str,"signal one");
		write (STDOUT_FILENO, (const void *) str, (size_t) strlen (str) + 1);
		

		exit (0);
	
}
void child(int * pipe){
		dup2 (pipe[READ], STDIN_FILENO);
		// point C
		close (pipe[READ]);
		close (pipe[WRITE]);
		// point D
		int num = read (STDIN_FILENO, (void *) str, (size_t)  sizeof (str));
		
		if (num > MAX) {
			perror ("pipe read error\n");
			exit(1);
		}
		puts (str);

}

void handler(int sig){
if(sig==SIGUSR1){
  printf("received a SIGUSER1 signal. signal Id: %d  \n", sig);

	}
if(sig==SIGUSR2){
  printf("received a SIGUSER2 signal signal Id: %d \n", sig);

}
}
