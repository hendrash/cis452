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
Dataset* shmptr;
int main(){

	Dataset* sharedMemory;
	
//Dataset* sharedMemory = &sharedMem;

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

	sigaction(SIGINT, &sigIntHandler,NULL);

	// ftok to generate unique key 
	signal(SIGSEGV,my_handler);
	if((key = ftok(".",1))<1){
		perror("IPC error: ftok"); 
		exit(1);
	}

	// shmget returns an identifier in shmid 
	shmid = shmget(key,shared_segment_size, S_IRUSR|S_IWUSR);
	if(shmid < 1){
		perror("Failed to assign shmid");
		exit(1);
	}
	cout<< "printing the shmid:"<<shmid << endl;
	//Attach struct to shared memory
	sharedMemory = (Dataset*) shmat(shmid, NULL, 0);


	shmptr=sharedMemory;
	if(sharedMemory->n==0)
		sharedMemory->writerTurn=0;

	bool myTurn = true;
	sharedMemory->n++;
	while(1) {

//		cout<<"Shared Memory "<<sharedMemory->userInput<<endl;
		// last one out shut the lights. This check for the last one out
		if(sharedMemory->n ==sharedMemory->numTimesRead){
			sharedMemory->numTimesRead = 0;
			sharedMemory->writerTurn = true; 
		}

		//provents a process from entering the critical section once it has entered once
		if(sharedMemory->writerTurn==true){
			myTurn = true;
		
		}

		// only print out onces	
		if(sharedMemory->writerTurn==false && myTurn) {
			myTurn=false;	
			sharedMemory->numTimesRead=sharedMemory->numTimesRead+1;
			cout<<"Shared Memory "<<sharedMemory->userInput<<endl;
			//printf("Other side: %s\n", sharedMemory->userInput);
		
		}
	} 

}


//When user enters ^C, print final stats before exiting the program
void my_handler(int shmid) {
	cout<<"Exsiting reader"<<endl;
	//notify everyone your leaving
	shmptr->n--;	
	
	shmid=shmptr->shmid;
	//detach from shared memory  
	shmdt(shmptr); 
	// destroy the shared memory 
	exit(0);
}


