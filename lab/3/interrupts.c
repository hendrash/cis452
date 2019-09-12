#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
pid_t pid;
if((pid=fork()) < 0){
	perror("forking error");
}
printf("%d",pid);
}
