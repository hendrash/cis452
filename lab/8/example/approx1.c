#include <stdio.h>
#include <string.h>
int power(int a, int b);
int approx(int);
void main(){
	printf("%d",approx(24672736));
}


int approx(int a){
int i=0;
	for(i=1; i<a;i=i*2);
	if(i==a)return i;
	i=i/2;
	return i+approx(a-i);
}

int power(int a, int b){
	if(b==0){return 1;}
	return a*power(a,(b-1));

}
