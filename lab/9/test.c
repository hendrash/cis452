#include<string.h>
#include<stdlib.h>
static char * init="data segments have been initialized with values";
static char * unit;
char *local(){
	char* stack="this information is kept on the stack";
	char* stack2="this information is kept on the stack";
return stack;}

int main(){
	char *compTime="Memory is allocated during compile time";
	static char* heap;
	heap=malloc(sizeof(char)*30);
	strcpy(heap, "This space is constructed at run time by the kernel");
	local();
}
