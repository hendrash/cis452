#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>

int main(int argc, char *argv[])
{ 	if(strcmp(argv[1], "-s")==0 ){
	symlink(argv[2],argv[3]);	
				 }
else{
link(argv[1], argv[2]);	}
	return 0;
}
