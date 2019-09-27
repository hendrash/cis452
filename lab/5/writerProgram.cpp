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
	string userInput;
}Dataset;

Dataset* sharedMemory;
const int shared_segment_size = sizeof(Dataset);
	
void my_handler(int num);

int main(){
	
	//set up sigHandler to receive ^C signal and call custom signal handler function
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
		
	// ftok to generate unique key 
    key_t key = ftok("shmfile",65);
	
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,shared_segment_size,IPC_CREAT); 
	
	//Attach struct to shared memory
	sharedMemory = (Dataset* ) shmat (shmid, 0, 0);
		
  
    // shmat to attach to shared memory 
    //char *str = (char*) shmat(shmid,(void*)0,0); 
	
	while(1) {
		//gets(str);
		if(sharedMemory.writerTurn) {
			cout << "Please provide data to be written into shared memory: ";
			cin >> sharedMemory.userInput;			
			printf("Data written into memory: %s\n",sharedMemory.userInput); 
			sharedMemory.writerTurn = 0;
		}
	}

}
	
	
//When user enters ^C, print final stats before exiting the program
void my_handler(int num) {
	
    //detach from shared memory  
    shmdt(sharedMemory);
	exit(0);
}


