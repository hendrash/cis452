#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
_Bool shmPredicate(long sharedMemorySize);
_Bool semPredicate(long counting);
long shmLimit(_Bool (*predicate)(long));
_Bool test1(long sharedMemorySize);
int approximate(int a,int b);
key_t key; int getKey();
void main(){
	getKey();
	printf("%lu <- test\n",shmLimit(test1));
	printf("%lu\n",shmLimit(shmPredicate));
	printf("%lu",shmLimit(semPredicate));
}

long shmLimit(_Bool (*predicate)(long)){
long j=0;
for(long i=0; i!=1; j=j+i/2){
	for(i=1;((*predicate)(i+j));i=i*2);
	}
	return j;
}

//TEST
_Bool test1(long a){
	return a<=385483187;
}
_Bool semPredicate(long size){
	int semid;
	if((semid=semget(IPC_PRIVATE,size,0))>0) {return 1;}
	return 0;
}
//This method needs some fixing 
_Bool shmPredicate(long sharedMemorySize){
	int shmid;
	if((shmid=shmget(key,sharedMemorySize,IPC_CREAT | 0600))>0){
	//	shmctl(shmid,IPC_RMID,NULL);
		return 1;}
	return 0;
}

int getKey(){
	if(key=ftok("./",1)<1){
		perror("Failed to assign shmid");
		exit(1);
	}
}



