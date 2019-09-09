#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h> 
#include "../clib/str.h"
#include <sys/times.h>
#include <sys/time.h>
#include <sys/resource.h>
int main(void) {
	
	char input [50];
	char *command;
	const int MAX = 10;
	char* parameters[MAX];
	pid_t pid, child; 
	static struct tms st_cpu;
	static clock_t st_time;
	static clock_t en_time;
	static struct tms en_cpu;
	int status;
	struct rusage buf;
	
	do {
		memset(input, 0, 50*sizeof(input[0]));	
		printf("Please enter a command with parameters: \n");
		printf(">");
		fgets(input, 50, stdin); //Fix this to work
		strcpy(input,strsegment(input,'\n'));
		
		char ** parstring=splitString(input,' ');
	
		/*
		command = strtok (input, " ");
		parameters[0] = command;
		int count = 1;
		while(*strtok (NULL, " ") != '\n') {
			parameters[count] = strtok (NULL, " ");
			printf("Value of params[%d] = %s\n", count, parameters[count] );
			++count;
		}*/

		// Start Time


	
		st_time=times(&st_cpu);
		strcpy(command, parstring[0]);	
		printf("value of parameters: ");	
		
		for(int i=0; parstring[i]!=NULL; i++){
			printf("%s ",parstring[i]);
		}

		printf("\n\nvalue for input is: :%s: \n\n", input);
		printf("value for command is: :%s: \n\n", command);

		//printf("value for params is: :%s: \n\n", parameters);

		pid = fork();
		
		if (pid < 0) {
			printf("ERROR: Fork operation failed");
			exit(1);
		} else if (pid) {
			wait(&status);
		} else {

			if (execve(command, parstring, 0) < 0) {
				perror("exec failed");
				exit(1);
			} 
		}

				//Currently nothing works thats because the execve is failing 	
				//  End Time	
				// https://linux.die.net/man/2/getrusage
				getrusage(RUSAGE_SELF, &buf);

				en_time=times(&en_cpu);
				printf("cpu time sec: %jd\n",(__intmax_t)((st_time)-times(&en_cpu)));

				printf("user cpu time used %ld \n", buf.ru_utime.tv_sec);

				printf("involuntary context switches: %ld\n", buf.ru_nivcsw);
	
	}while (strcmp(input,"quit"));

	return 0;
}

