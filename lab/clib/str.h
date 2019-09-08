#include<stdio.h>
#include<string.h>
#include<stdlib.h>
// For testing

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

