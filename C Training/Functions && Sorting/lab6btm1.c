
#include<stdio.h>
#include<ctype.h>

int main(int argc, char *argv[]) {

char s[21],p[21];
char x;
int j,i,v,k;
printf("Enter word :");
scanf("%s" , s);
	do { printf("Enter delimiter :");
scanf("%c", &x);
	}while(isalnum(x));
	
for(i=0; i<=20; i++) {
	if (s[i]==x) j=i; }

	for(i=20; i==0; i--) {
		if (s[i]==x) 
			k=i;
	}
	v=0;
	for(i=0; s[i]==j-1; i++) {
		p[v]=s[i];
		v=v+1;
	}
	v=0;
	for(i=k+1; i<=20; i++) {
		p[v]=s[i];
		v=v+1;
	}
	printf("%s", p);
	if(k==0 || j==0) { printf("Not found\n"); }
	
	
	return(0);
}
