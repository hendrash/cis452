#include<iostream>
#include<thread>
#include<mutex>
#include<unistd.h>
using namespace std;
mutex mtx;
string returnFile(string fname);
void getFile();

int main(){
getFile();
}

void getFile(){
	string fileName;
	cout <<"Enter in a file name .... \n";
	
	cin >> fileName;
	cout <<	returnFile(fileName);	
}

string returnFile(string fname){
	if(rand()%11>7){
		int sleepTime=7+rand()%4;
		sleep(sleepTime);
		return fname;
	}
	else{
		sleep(1);
		return ("retrieved file " + fname+" from database successfully\n");

	}
}

