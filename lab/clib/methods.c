#include "header.h"
#include <dirent.h>
int cmpstr(char* str1, char* str2){
	int i =0;
		while(str1[i] != '\n'&&str1[i] !='\000'&&str2[i] !='\n'&&str2[i] !='\000'){
		if(str1[i] != str2[i]){
		return 0;	
		}
	i++;	
	}
		return 1;
}
char* list(){
char * content=(char *)malloc(sizeof(char)*2048);
memset(content,0,sizeof(content));
int i=0;
int c=0;
DIR *d;
struct dirent *dir;
d=opendir(".");
if(d){
	strcat(content, "\n");
	while ((dir =readdir(d)) != NULL)
	{
		strcat(dir->d_name," 	 ");
		strcat(content,dir->d_name);
		if(c>5)
		{
			strcat(content,"\n");
			c=0;
		}
		c++;
	}
	closedir(d);
}

return content;
}

void writeTofile(char* file, char* data){
FILE *outfile;
outfile=fopen(file, "w");
fprintf(outfile, "%s\n", data);
fclose(outfile);
}

char* readFile(char file[]){
 FILE *fp;
    
char* temp=(char *)malloc(sizeof(char)*2048);
char* str=(char *)malloc(sizeof(char)*2048);
memset(str,0,sizeof(str));
unsigned i=0;
    fp = fopen(file, "r");
    if (fp == NULL){
        printf("Could not open file %s",file);
        return NULL;
    }
    while (fgets(temp, 2048, fp) != NULL){
        printf("%s", temp);
	strcat(str, temp);
    }
    fclose(fp);
    return str;
}
char* strsegment(char *str, char garbage) {
char* s=(char*)malloc(sizeof(char)*2048);
memset(s,0,sizeof(s));
int i=0;
	while(str[i] != garbage&&str[i] !='\000'){
	s[i]=str[i];
		i++;
	}
	return s;
}
unsigned countWords(char* str)
{ 
    unsigned i =0;
    unsigned wc = 0;  // word count

    // Scan all characters one by one
    while (*str!='\n')
    {
        // If next character is a separator, set the
        // state as OUT
        if (*str == ' ' || *str == '\000' || *str == '\t')
	wc++;
        // If next character is not a word separator and
        // state is OUT, then set the state as IN and
        // increment word count

        // Move to next character
        ++str;
    }

    return wc;
}
