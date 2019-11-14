#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
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
   while ((entryPtr = readdir (dirPtr))) {
     if (stat (filePathPtr, &statBuf) < 0) {
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
   return 0;
}