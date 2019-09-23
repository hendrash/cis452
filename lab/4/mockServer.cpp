#include<iostream>
#include<thread>
#include <pthread.h>
#include <string> 
#include <stdlib.h>
#include<mutex>
#include <errno.h>
#include<unistd.h>
#include <signal.h>

#define NUM_THREADS 100

using namespace std;
mutex mtx;
double totalAccessTime;
int numTimesAccessed;
int counter = 0;
pthread_t threads[NUM_THREADS];
string fileName; 

void *returnFile(void* arg);
void getFile();
void my_handler(int num);

int main(){
	
	//set up sigHandler to receive ^C signal and call custom signal handler function
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
   
	while(1)
		getFile();
}

void getFile(){
	
	cout <<"Enter in a file name .... \n";
	cin >> fileName;
	int status;

	//Creates thread and assigns it to execute the returnFile function with fileName as an argument
	if ((status = pthread_create (&threads[counter], NULL, returnFile, &fileName)) != 0) {
        cerr << "thread create error: " << endl;
        exit (1);
    }
}

void *returnFile(void* arg){
	
	string fname = *reinterpret_cast<std::string*>(arg);
	
	if(rand()%11>7){
		int sleepTime=7+rand()%4;
		mtx.lock();
		totalAccessTime += sleepTime;
		++numTimesAccessed;
		++counter;
		mtx.unlock();
		sleep(sleepTime);
		cout <<"retrieved file " << fname << " from database successfully" << endl;
	}
	else{
		sleep(1);
		mtx.lock();
		++totalAccessTime;
		++numTimesAccessed;
		++counter;
		mtx.unlock();
		cout <<"retrieved file " << fname  << " from database successfully" << endl;
	}
	
	//Once the current thread has finished its work, it needs to detech from the parent thread and then properly end itself
	pthread_detach(pthread_self());
	pthread_exit(NULL); 
}	
	
//When user enters ^C, print final stats before exiting the program
void my_handler(int num) {
	
	cout <<" Total number of file requests received: " + std::to_string(numTimesAccessed) + "\n";
	cout <<"Average file access time: " + std::to_string((totalAccessTime / numTimesAccessed)) + "\n";
	exit(0);
}


