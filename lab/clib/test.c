#include "str.h"
#include<string.h>
#include<stdio.h>
int main(){
	char** hello =splitString("strtok needs to be called several times to split a string hii ihaf asfd",' ');
	    
	for(int i=0; hello[i] !=NULL ;i++){
	i++;	
		printf("%s\n",hello[i]);
	}
	

	
}

