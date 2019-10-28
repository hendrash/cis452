#include<string.h>
#include<stdlib.h>
static char * init="data segments have been initialized with values";
static char * uninit;

char *local(){
	char* stack="this information is kept on the stack";
return stack;}

int main(){
	char *compTime="Memory is allocated during compile time";
	uninit=	malloc(sizeof(char)*30);
	strcpy(uninit, "This space is constructed at run time by the kernel");
	local();
}
