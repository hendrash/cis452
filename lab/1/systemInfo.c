#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>


int main(){
	char *userName;
	char *hostName ="";
	char hostBuffer[1024];
	gethostname(hostBuffer, sizeof(hostBuffer));
	userName=getlogin();
	register uid_t userId=getuid();
	register gid_t gid = getgid();
	printf("=======================================\n");
	printf("user is: %s \n",userName);
	printf("uid is: %i \n", userId);
	printf("gid is: %i \n", gid);
	printf("host is: %s \n\n",hostBuffer);
	for(int i=0;i<5;i++){
	printf("entry is: %s \n", getpwent()->pw_name);}
	printf("=======================================");
return 0;
}
