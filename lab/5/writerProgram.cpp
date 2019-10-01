#include <iostream>
#include <thread>
#include <pthread.h>
#include <string> 
#include <stdlib.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>
#include <errno.h>
#include<unistd.h>
#include <signal.h>
#include "DataSet.h"

using namespace std;

const int shared_segment_size = sizeof(Dataset);

void my_handler(int num);

int main(){
	Dataset sharedMemory;
	sharedMemory.writerTurn=1;
	Dataset * shm_ptr=&sharedMemory;
	int shmid;	
	key_t key;
	//set up sigHandler to receive ^C signal and call custom signal handler function
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	// ftok to generate unique key 
	if((key=ftok("./",65))<1){
		perror("Failed to assign shmid");
		exit(1);
	}

	// shmget returns an identifier in shmid 
	if((shmid = shmget(key,shared_segment_size,IPC_CREAT))){
		perror("Failed to assign shmid");
	}
        	
	//Attach struct to shared memory
	shm_ptr = (Dataset* ) shmat (shmid, 0, 0);
	
	// shmat to attach to shared memory 
	//char *str = (char*) shmat(shmid,(void*)0,0); 

	while(1) {
		if(sharedMemory.writerTurn) {
			cout << "Please provide data to be written into shared memory: ";
			cin >> sharedMemory.userInput;			
			printf("Data written into memory: %s\n",sharedMemory.userInput.c_str()); 
			sharedMemory.writerTurn = 0;
		}
	}
}

//When user enters ^C, print final stats before exiting the program
void my_handler(int shmid) {
	//detach from shared memory  
//	shmdt(sharedMemory);
	exit(0);
}


