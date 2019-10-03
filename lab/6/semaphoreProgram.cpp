#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define SIZE 16

struct sembuf sBuf;

int main (int argc, char *argv[])
{
   int status;
   long int i, loop, temp, *shmPtr;
   int shmId;
   int semId;
   pid_t pid;

      // get value of loop variable (from command-line argument)
      loop = atoi(argv[1]);
	  
	  //create a new semaphore set for use by this (and other) processes
	  semId = semget (IPC_PRIVATE, 1, 00600));
	  
	  //initialize the semaphore set referenced by the previously obtained semId handle
	  semctl (semId, 0, SETVAL, 1);

   if ((shmId = shmget (IPC_PRIVATE, SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) {
      perror ("i can't get no..\n");
      exit (1);
   }
   if ((shmPtr = shmat (shmId, 0, 0)) == (void*) -1) {
      perror ("can't attach\n");
      exit (1);
   }

   shmPtr[0] = 0;
   shmPtr[1] = 1;

   if (!(pid = fork())) {
	   //code here semop()
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[0] and shmPtr[1]
               temp = shmPtr[0];
               shmPtr[0] = shmPtr[1];
               shmPtr[1] = temp;

      }
	  //code here semop()
      if (shmdt (shmPtr) < 0) {
         perror ("just can't let go\n");
         exit (1);
      }
      exit(0);
   }
   else
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[1] and shmPtr[0]
               temp = shmPtr[1];
               shmPtr[1] = shmPtr[0];
               shmPtr[0] = temp;
      }

   wait (&status);
   printf ("values: %li\t%li\n", shmPtr[0], shmPtr[1]);
   if (shmdt (shmPtr) < 0) {
      perror ("just can't let go\n");
      exit (1);
   }
   if (shmctl (shmId, IPC_RMID, 0) < 0) {
      perror ("can't deallocate\n");
      exit(1);
   }
   
   // remove the semaphore referenced by semId - may need to move the location of this line
	semctl (semId, 0, IPC_RMID);

   return 0;
}