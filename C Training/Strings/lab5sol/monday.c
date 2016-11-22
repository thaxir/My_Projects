#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define SIZE 21

int main () {
	char word[SIZE];
	char letter;
	char formatstring[13];

	int i, j;

	sprintf(formatstring, "%%%ds", SIZE-1);

	printf("Enter word: ");
	scanf(formatstring, word);

	do {
		printf("Enter letter: ");
		scanf(" %c", &letter);
	} while (!isalpha(letter));

	for (i=0; word[i]!='\0'; i++)  {
		if (word[i]==letter) {
			for (j=i; word[j] !='\0'; j++) {
				word[j]=word[j+1];
			}
			i--; /* to account for successive occurrences */
		}
	}
	printf("%s\n", word);	
	return 0;
}
	
			
