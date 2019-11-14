#include<unistd.h>
#include<string.h>
#include<stdlib.h>
static char * init="data segments have been initialized with values";
static char * unit;
int main(){
	char *compTime="Memory is allocated during compile time";
	static char* heap;
	static char* heap2;
	
	heap=malloc(sizeof(char)*30);
	heap2=malloc(sizeof(char)*30);
	strcpy(heap, "This space is constructed at run time by the kernel");
	strcpy(heap2, "This space is constructed at run time by the kernel");
	char stack='t';
	char stack2='s';
	pause();
}
