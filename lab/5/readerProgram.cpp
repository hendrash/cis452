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
#include <sys/stat.h>
#include "DataSet.h"
using namespace std;

const int shared_segment_size = sizeof(Dataset);

void my_handler(int shmid);

int main(){

	Dataset sharedMemory;
	sharedMemory.writerTurn=0;
	Dataset* shm_ptr = &sharedMemory;

	int shmid; 
	key_t key; 
	//set up sigHandler to receive ^C signal and call custom signal handler function
	//Fancy Singal handler
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	/*
	 * The sigemptyset() function is part of a family of functions that manipulate signal sets. Signal sets are data objects that let 
	 * a thread keep track of groups of signals. For example, a thread might create a signal set to record which signals it is 
	 * blocking, and another signal set to record which signals are pending. */
	sigemptyset(&sigIntHandler.sa_mask);
	
	sigIntHandler.sa_flags = 0;
	
	sigaction(SIGINT, &sigIntHandler, NULL);

	// ftok to generate unique key 
	if((key = ftok(".",65))<1){
		perror("IPC error: ftok"); 
		exit(1);
	}

	// shmget returns an identifier in shmid 
	if((shmid=shmget(key,shared_segment_size, IPC_CREAT|S_IRUSR|S_IWUSR)<1)){
		perror("Failed to assign shmid");
		exit(1);
	}
       cout<< "printing the shmid:"<<shmid << "\n";
	//Attach struct to shared memory
	shm_ptr= (Dataset*) shmat (shmid, NULL, 0);
	
	if(shm_ptr==(Dataset*)-1){
		perror("shmat error");
		exit(1);	
	}

	bool myTurn = true;
	while(1) {
		if(sharedMemory.writerTurn==0 && myTurn) {
			printf("Data read from memory: %s\n",sharedMemory.userInput.c_str());
			sharedMemory.numTimesRead = sharedMemory.numTimesRead + 1;			
			if(sharedMemory.numTimesRead == 2) {
				//Reset number of times read for next round
				sharedMemory.numTimesRead = 0;
				//Set turn back to writer so it can write again
				sharedMemory.writerTurn = 1;
				myTurn = true;
			}
			myTurn = false;
		}
	} 

}


//When user enters ^C, print final stats before exiting the program
void my_handler(int shmid) {

	//detach from shared memory  
//	shmdt(sharedMemory); 
	// destroy the shared memory 
///	shmctl(shmid,IPC_RMID,NULL);
	exit(0);
}


