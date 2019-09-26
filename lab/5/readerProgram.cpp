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

#define NUM_THREADS 100

using namespace std;
int turn = 1; 


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
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 
    char *str = (char*) shmat(shmid,(void*)0,0); 
	
	while(1) {
		if(turn == 1) {
			printf("Data read from memory: %s\n",str); 
		}
	}       

}
	
	
//When user enters ^C, print final stats before exiting the program
void my_handler(int num) {
	
	//detach from shared memory  
    shmdt(str); 
    // destroy the shared memory 
    shmctl(shmid,IPC_RMID,NULL);
	exit(0);
}


