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
#define MUTEX 2

//sBuf has 3 properties in it: unsigned short sem_num, short sem_op, and short sem_flg
struct sembuf waitBuf = { 0, -1, 0 };
struct sembuf signalBuf = { 0, 1, 0 };

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
	  if((semId = semget (IPC_PRIVATE, 1, 00600)) < 0) {
		perror ("semget failed\n");
		exit (1);
	  }
	  
	  //initialize the semaphore set referenced by the previously obtained semId handle
	  if(semctl (semId, 0, SETVAL, 1) < 0) {
		perror ("semctl initialization failed\n");
		exit (1);  
	  }

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
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[0] and shmPtr[1]
			   //critical section!!
			   semop(semId, &waitBuf, 1); 
               temp = shmPtr[0];
               shmPtr[0] = shmPtr[1];
               shmPtr[1] = temp;
			   semop(semId, &signalBuf, 1); 
      }
      if (shmdt (shmPtr) < 0) {
         perror ("just can't let go\n");
         exit (1);
      }
      exit(0);
   }
   else
      for (i=0; i<loop; i++) {
               // swap the contents of shmPtr[1] and shmPtr[0]
			   //critical section!!
			   semop(semId, &waitBuf, 1); 
               temp = shmPtr[1];
               shmPtr[1] = shmPtr[0];
               shmPtr[0] = temp;
			   semop(semId, &signalBuf, 1); 
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
	if(semctl (semId, 0, IPC_RMID) < 0) {
	  perror ("error removing semaphore\n");
      exit(1);
	}

   return 0;
}
