#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <string.h>
#include <string.h>
#include <string.h>

long shmLimit();
long approx(long j);
_Bool shmPredicate(long sharedMemorySize);
_Bool test1(long sharedMemorySize);
int approximate(int a,int b);
key_t key; int getKey();
void main(){
	getKey();
	printf("%lu",shmLimit());
}
long shmLimit(){
long i,j=0;
	while(i!=1){
		for(i=1;shmPredicate(i+j);i=i*2);
		j=j+i/2;
	}
	return j;
}


_Bool test1(long a){
	return a<=385483187;
}

//	if(!test(i+j)&&test((i+j)-1)){
_Bool shmPredicate(long sharedMemorySize){
	int shmid;
	if((shmid=shmget(key,sharedMemorySize,IPC_CREAT | 0600))>0){		shmctl(shmid,IPC_RMID,NULL);
		return 1;}
	return 0;
}

int getKey(){
	if(key=ftok("./",1)<1){
		perror("Failed to assign shmid");
		exit(1);
	}
}


int approximate(int a,int j){
	int i=1;
	for(; j+i<a;i=i*2);// see if through error
	if(i+j==a)return i;// see if through error
	i=i/2;
	return i+approximate(a,i+j);
}



long approx(long j){
	long i=0;
	for(i=1; shmPredicate(i+j);i=i*2);// see if through error
	if(i==1){
		return j;}// see if through error
	i=i/2;
	return approx(j+i);
}


