#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	char input [50];
	char command [10];
	char *parameters;
	pid_t pid, child; 
    int status;
	
	while (input != "quit") {
		
	printf("Please enter a command with parameters: ");
	scanf("%s",input);
	
	command = 
	parameters = strchr(input, ' ')
	
	pid = fork();
	
	if (pid < 0) {
		printf("ERROR: Fork operation failed");
		exit(1);
	} else if (pid) {
		wait(-1, &status);
	} else {
		execve(command, parameters); //TODO this nonsense
	}
		
		
	}

    if (execvp(command, &argv[1]) < 0) {
        perror("exec failed");
        exit(1);
    }
    puts("After the exec");

    return 0;
}