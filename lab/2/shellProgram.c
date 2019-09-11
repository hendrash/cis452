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
	pid_t pid, child; 
	static struct tms st_cpu;
	static clock_t st_time;
	static clock_t en_time;
	static struct tms en_cpu;
	int status;
	struct rusage buf;
	char* string[64];
	long lastTotal = 0;
	
	do {
		memset(input, 0, 50*sizeof(input[0]));	
		printf("Please enter a command with parameters: \n");
		printf(">");
		fgets(input, 50, stdin); //Fix this to work
		printf("\n\n");
		strcpy(input,strsegment(input,'\n'));

		execParse(input, string);

		st_time=times(&st_cpu);
	
		pid = fork();
		
		if (pid < 0) {
			printf("ERROR: Fork operation failed");
			exit(1);
		} else if (pid) { //parent's code
			wait(&status);
		} else { //everything in here is the child's code
			int i =0;
			printf("Command entered was" );
		//	while( parstring[i]!=NULL){ printf("(:%s:)\n", parstring[i]); i++;}
			if (execvp(*string,string) < 0) {
				perror("exec failed");
				exit(1);
			} 
			getrusage(RUSAGE_SELF, &buf); //RUASGE_CHILDREN

			en_time=times(&en_cpu);

			printf("\n\n\n\n\n");
			//printf("cpu time sec: %jd\n",(__intmax_t)((st_time)-times(&en_cpu))); <- We don't need this
			
			printf("user cpu time used %ld \n", (buf.ru_utime.tv_sec - lastTotal));

			printf("involuntary context switches: %ld\n", buf.ru_nivcsw);
			printf("\n\n\n\n\n");
			
			lastTotal = buf.ru_utime.tv_sec;
		}
	
	}while (strcmp(input,"quit"));

	return 0;
}

