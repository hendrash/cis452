#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
   //declare variables
   struct stat statBuf;
   DIR *dirPtr;
   struct dirent *entryPtr;

   //open stream in current directory for reading in data
   dirPtr = opendir (".");

   //loop through every file in the current directory, and print out its statistics
   while ((entryPtr = readdir (dirPtr))) {
      printf ("%-20s\n", entryPtr->d_name);
     if (stat (entryPtr->d_name, &statBuf) < 0) {
        perror ("huh?  there is ");
        exit(1);
     } else {
	   printf ("value is: %u\n", S_ISREG(statBuf.st_mode));
       printf ("Size in bytes is: %li\n", statBuf.st_size);
     }
    }
	
   //close data stream
   closedir (dirPtr);
   return 0;
}