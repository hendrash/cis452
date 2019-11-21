#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   //declare variables
   struct stat statBuf;
   DIR *dirPtr;
   struct dirent *entryPtr;
   char *filePathPtr;
   char actualpath [4096+1];
   
    if (argc < 2) {
      printf ("Usage: directory name required\n");
      exit(1);
    }
	
	//Take user-specified directory and create an absolute path to it
	if((filePathPtr = realpath(argv[1], actualpath)) == NULL) {
	  printf ("Usage: realpath failed\n");
      exit(1);
	}

   //open stream in the specified directory for reading in data
   dirPtr = opendir (filePathPtr);
   
   //loop through every file in the specified directory, and print out its statistics
   char *currentFilePath = malloc(150);
   while ((entryPtr = readdir (dirPtr))) {
	   strcpy(currentFilePath, filePathPtr);
	   strcat(currentFilePath, "/");
	   strcat(currentFilePath, entryPtr->d_name);
     if (lstat (currentFilePath, &statBuf) < 0) {
		printf ("Path that errored out: %s ", currentFilePath);
        perror ("huh?  there is ");
        exit(1);
     } else {
	   //print file statistics
	   printf ("User ID: %u ", statBuf.st_uid);
	   printf ("Group ID: %u ", statBuf.st_gid);
       printf ("Inode number: %li ", entryPtr->d_ino);
	   printf ("%-20s\n", entryPtr->d_name);
     }
    }
	
   //close data stream
   closedir (dirPtr);
   free(currentFilePath);
   return 0;
}