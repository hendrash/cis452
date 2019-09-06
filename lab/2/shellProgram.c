#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	char input [50];
	const char *command;
	char* parameters;
	pid_t pid, child; 
    int status;
	
	while (input != "quit") {
		
		printf("Please enter a command with parameters: ");
		scanf("%s",input); //he wants us to use fgets?
		
		command = strtok (input, " ");
		parameters = strtok (NULL, " ");
		
				printf("value for input is: %s \n", input);
		printf("value for command is: %s \n", command);
		printf("value for params is: %s \n", parameters);
		
		pid = fork();
		
		if (pid < 0) {
			printf("ERROR: Fork operation failed");
			exit(1);
		} else if (pid) {
			wait(-1, &status);
		} else {
			if (execve(command, parameters, 0) < 0) {
				perror("exec failed");
				exit(1);
			}	
		}
	}

    return 0;
}