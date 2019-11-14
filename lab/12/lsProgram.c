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
   
    if (argc < 2) {
      printf ("Usage: diractory name required\n");
      exit(1);
    }

   //open stream in the specified directory for reading in data
   dirPtr = opendir (argv[1]);

   //loop through every file in the specified directory, and print out its statistics
   while ((entryPtr = readdir (dirPtr))) {
     if (stat (entryPtr->d_name, &statBuf) < 0) {
        perror ("huh?  there is ");
        exit(1);
     } else {
	   //printf ("value is: %u\n", S_ISREG(statBuf.st_mode));
	   printf ("User ID: %u ", statBuf.st_uid);
	   printf ("Group ID: %u ", statBuf.st_gid);
	   //printf ("Size (bytes): %li", statBuf.st_size);
       printf ("Inode number: %li ", entryPtr->d_ino);
	   printf ("%-20s\n", entryPtr->d_name);
     }
    }
	
   //close data stream
   closedir (dirPtr);
   return 0;
}