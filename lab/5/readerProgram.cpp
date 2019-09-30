#include<iostream>
#include<thread>
#include <pthread.h>
#include <string> 
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <errno.h>
#include<unistd.h>
#include <signal.h>

using namespace std;

typedef struct Dataset{
	int writerTurn;
	int numTimesRead;
	string userInput;
}Dataset;

Dataset* sharedMemory;
const int shared_segment_size = sizeof(Dataset);

void my_handler(int shmid);

int main(){
	int shmid; 
	//set up sigHandler to receive ^C signal and call custom signal handler function
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	// ftok to generate unique key 
	key_t key = ftok("shmfile",65);

	// shmget returns an identifier in shmid 
	if(shmget(key,shared_segment_size,IPC_CREAT)){
		perror("Failed to assign shmid");
	} 
	//Attach struct to shared memory
	sharedMemory = (Dataset* ) shmat (shmid, 0, 0);

	bool myTurn = true;
	while(1) {

		if(!sharedMemory->writerTurn && myTurn) {
			printf("Data read from memory: %s\n",sharedMemory->userInput.c_str());
			sharedMemory->numTimesRead = sharedMemory->numTimesRead + 1;			
			if(sharedMemory->numTimesRead == 2) {
				//Reset number of times read for next round
				sharedMemory->numTimesRead = 0;
				//Set turn back to writer so it can write again
				sharedMemory->writerTurn = 1;
				myTurn = true;
			}
			myTurn = false;
		}
	} 

}


//When user enters ^C, print final stats before exiting the program
void my_handler(int shmid) {

	//detach from shared memory  
	shmdt(sharedMemory); 
	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL);
	exit(0);
}


