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
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <unistd.h>
using namespace std;

const int shared_segment_size = sizeof(Dataset);

void my_handler(int num);
Dataset * shmptr;
int main(){
	Dataset * sharedMemory;
	int shmid;	
	key_t key;
	//set up sigHandler to receive ^C signal and call custom signal handler function
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	// ftok to generate unique key 
	if((key=ftok("./",1))<1){
		perror("Failed to assign shmid");
		exit(1);
	}

	// shmget returns an identifier in shmid 
	shmid = shmget(key,shared_segment_size,IPC_CREAT | 0600);
	if(shmid < 1){
		perror("Failed to assign shmid");
	}
        	
	//Attach struct to shared memory
	sharedMemory = (Dataset* ) shmat (shmid,NULL, 0);

	// sets sharedMemorys values
	
	sharedMemory->shmid=shmid;	
	sharedMemory->writerTurn=true;
	sharedMemory->n=0;
	sharedMemory-> numTimesRead=0;
	memset(sharedMemory->userInput, '\000', sizeof(sharedMemory->userInput));
	
	shmptr=sharedMemory;
	if(sharedMemory==(Dataset*)-1){
	perror("shmat failed ");
	exit(1);
	}
	// shmat to attach to shared memory 
	//char *str = (char*) shmat(shmid,(void*)0,0);
cout<< "printing the shmid:"<<shmid << "\n";	

	while(1) {
		if(sharedMemory->writerTurn) {
			cout << "Please provide data to be written into shared memory: ";
			cin >> sharedMemory->userInput;			
			printf("Data written into memory: %s\n",sharedMemory->userInput); 
			sharedMemory->writerTurn = false;
		}
	}
}

//When user enters ^C, print final stats before exiting the program
void my_handler(int shmid) {
	shmid=shmptr->shmid;
	//detach from shared memory  
	if(shmdt(shmptr)==-1){
	perror("failed to detach");
	}

	if(shmctl(shmid,IPC_RMID,NULL)==-1){
	perror("failed to remove shared memory");
	}
cout<< "exiting writer "<<endl;
exit(0);
}


