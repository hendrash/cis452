#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    size_t len=16;
    printf ("Please input username: ");
    char c;
    char* str=malloc(sizeof(char)*len);
    len=0;
    while(EOF!=(c=fgetc(stdin)) && c !='\n'){
	    str[len++]=c;	    
	    if(len%16==0)
	    str=realloc(str, sizeof(char)*(len+16));
    }
    str[len++]='\0';
    printf("you entered %s\n",str);	
    free(str);
    return 0;
}
