#include<iostream>
#include<thread>
#include<mutex>
#include<unistd.h>
#include <signal.h>

#define NUM_THREADS 10

using namespace std;
mutex mtx;
double totalAccessTime;
int numTimesAccessed;
string returnFile(string fname);
void getFile();

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
	
	pthread_t thread[NUM_THREADS];
	string fileName;
	cout <<"Enter in a file name .... \n";
	cin >> fileName;
	
	//Creates thread and assigns it to execute the returnFile function with fileName as an argument
	if ((status = pthread_create (&thread1, NULL,  returnFile, fileName)) != 0) {
        cerr << "thread create error: " << strerror(status) << endl;
        exit (1);
    }
}

string returnFile(string fname){
	
	if(rand()%11>7){
		int sleepTime=7+rand()%4;
		mtx.lock();
		totalAccessTime += sleepTime;
		++numTimesAccessed;
		mtx.unlock();
		sleep(sleepTime);
		return fname;
	}
	else{
		sleep(1);
		mtx.lock();
		++totalAccessTime;
		++numTimesAccessed;
		mtx.unlock();
		cout <<"retrieved file " + fname+" from database successfully\n");

	}
	
	//When user enters ^C, print final stats before exiting the program
	void my_handler(int num) {
		
		cout <<"Total number of file requests received: " + numTimesAccessed;
		cout <<"Average file access time: " + (totalAccessTime / numTimesAccessed);
		exit(0);
	}
}

