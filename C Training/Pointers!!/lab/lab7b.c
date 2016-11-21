#include<string.h>
#include<stdio.h>

#define SIZE 20

int main (int argc, char *argv[]) {
	int i,j,lim;
	char string[SIZE];
	char formatstring[15];
	char c;

	printf("Enter string: ");
	sprintf(formatstring, "%%%ds", SIZE-1);
	scanf(formatstring, string);
	
	

	printf("%s\n", string);
	return 0;
}
