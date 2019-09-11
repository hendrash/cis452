#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h> 
#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "../clib/clib.h"
int main(void) {
	
	char input [50];
	pid_t pid; 
	int status;
	struct rusage buf;
	char* string[64];
	long lastTotal = 0;
	
	do {
		memset(input, 0, 50*sizeof(input[0]));	
		printf("Please enter a command with parameters: \n");
		printf(">");
		fgets(input, 50, stdin); 
		printf("\n\n");
		strcpy(input,strsegment(input,'\n'));

		execParse(input, string);

	
		pid = fork();
		
		if (pid < 0) {
			printf("ERROR: Fork operation failed");
			exit(1);
		} else if (pid) { //parent's code
		
			wait(&status);
			
			getrusage(RUSAGE_CHILDREN, &buf); //Monitors total usage for all children


			printf("\n\n\n\n\n");			
			printf("user cpu time used sec: %ld \n", (buf.ru_utime.tv_usec - lastTotal));

			printf("involuntary context switches: %ld\n", buf.ru_nivcsw);
			printf("\n\n\n\n\n");
			
			lastTotal = buf.ru_utime.tv_sec;
			
		} else { //everything in here is the child's code
			printf("Command entered was" );
			if (execvp(*string,string) < 0) {
				perror("exec failed");
				exit(1);
			} 
		}
	
	}while (strcmp(input,"quit"));

	return 0;
}

