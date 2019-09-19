#include<iostream>
#include<thread>
#include<mutex>
#include<unistd.h>
using namespace std;
mutex mtx;
int main(){

}

void getFile(){
	string fileName;
	cout <<"Enter in a file name .... \n";
	cin >> fileName;

}

string returnFile(string fname){
if(rand()%11>7){
int sleepTime=7+rand()%4;
sleep(sleepTime);
return fname;
}
else{
	sleep(1);
	return fname;

}
}

