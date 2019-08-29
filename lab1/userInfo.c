#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
	char *userName;
//	char *userId;
	char *groupId;
	char *hostName;

	userName=getlogin();
	register uid_t userId=getuid();
	register gid_t gid = getgid();
	
	printf("user is: %s \n",userName);
	printf("uid is: %i \n", userId);
	printf("gid is: %i \n", gid);
	printf("host is: \n");
	printf("entry is:\n");
	
return 0;
}
