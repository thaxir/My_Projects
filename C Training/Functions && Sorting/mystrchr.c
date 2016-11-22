/* Frontistirio 18/11
   Diki mas ulopoiisi tis strchr */

#include<stdio.h>
#define SIZE 20

char * mystrchr(char str[], char ch);

int main (int argc, char *argv[]) {
	char str[SIZE], ch;

	char format[15];
	sprintf(format, "%%%ds", SIZE-1); 
	printf("Enter string: ");
	scanf(format, str);
	printf("Enter character: ");
	scanf(" %c", &ch);

	if (mystrchr(str, ch)) {
		printf("O xaraktiras brisketai sti leksi\n");
	}
	else {
		printf("O xaraktiras de brisketai sti leksi\n");
	}
	return 0;
}


char * mystrchr(char str[], char ch) {
	int i;
	for (i=0; str[i]!='\0'; i++) {
		if (str[i] == ch) {
			return &str[i];
		}
	}
	return NULL;
}
