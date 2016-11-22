#include<stdio.h>
#include<string.h>

#define SIZE 21

int main () {
	char str[SIZE];
	char delim;
	char formatstring[13];

	int left, right;
	int i, copyIndex;

	sprintf(formatstring, "%%%ds", SIZE-1);

	printf("Enter word: ");
	scanf(formatstring, str);

	do {
		printf("Enter delimiter: ");
		scanf(" %c", &delim);
	} while (!isalnum(delim));

	for (left=0; left<strlen(str) ; left++) 
		if (str[left]==delim) break; 

	for (right=strlen(str); right>=0; right--) 
		if (str[right]==delim) break; 

	int toCopy = strlen(str)-right+1;
	for (i=0, copyIndex=left; i<toCopy; i++, copyIndex++) {
		str[copyIndex]=str[right+i+1];
	}
	printf("%s\n", str);	
	return 0;
}
	
			
