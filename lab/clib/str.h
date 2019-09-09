#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int twoDLength(void** arr){
  int i=0;
	for(int i; arr[i] !=NULL ;i++);
  return i;
}
int * getDelimLength(char *str,char del){
//row |^,-> column	
	int row=1;
	int col=1;
	int temp=1;
	int length= strlen(str);
	for(int i=0; i<length;i++){
		if(str[i]==del){
			row++;
			col=0;	
		}
		if(col>temp){
		temp++;
		}
		col++;
	}
	col=temp;
	int *vector= malloc(2*sizeof(int));
	vector[0]=row;
	vector[1]=col;
	
	return vector;
}

// parses a string 
char ** splitString(char* str, char delim){
	int * vec=getDelimLength(str, delim);
	char **parString = (char **)malloc(vec[0]*sizeof(char*));
	for(int i =0; i<vec[0]; i++){
		parString[i]=(char *)malloc(vec[1]*sizeof(char));
	}
	int j=0;
	int k=0;
	int length=strlen(str);
	for(int i =0; i <= length; i++)
	{
		if(str[i]==delim){
		j++;
		k=0;
		}else{
		parString[j][k]=str[i];
		k++;
		}
	}
	return parString;
	}


char* strsegment(char *str, char garbage) {
char* s=(char*)malloc(sizeof(char)*2048);
memset(s,0,sizeof(char)*2048);
int i=0;
	while(str[i] != garbage&&str[i] !='\000'){
	s[i]=str[i];
		i++;
	}
	free(s);
	return s;
}

//int main(){
//printf("%s",strsegment("hello\n", '\n'));
//}

