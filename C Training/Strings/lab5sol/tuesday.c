#include<stdio.h>
#include<string.h>

#define WORDLENGTH 21
#define INSETLENGTH 4

int main (int argc, char *argv[]) {
	char word[WORDLENGTH], inset[INSETLENGTH];
	char formatstring[15];
	
	int i, j;
	int dashes, dashpos;

	sprintf(formatstring, "%%%ds", WORDLENGTH-1);
	do {
		scanf(formatstring, word);
		dashes = 0; /* poses paules exei i leksi */
		dashpos = -1; /* se poia thesi einai i paula */
		for (i=0; word[i]!='\0'; i++) {
			if (word[i]=='-') {
				dashes++;
				dashpos = i;
			}
		}
	} while (dashes != 1);

	sprintf(formatstring, "%%%ds", INSETLENGTH-1);
	scanf(formatstring, inset);

	for (j=0; j<strlen(inset)-1; j++) { /* Gia osous xaraktires exei to inset... */
		/* ...metefere olous tous xaraktires tis leksis meta tin paula
		mia thesi deksia (pigainontas apo deksia pros aristera.*/
		for (i=WORDLENGTH-1; i>=dashpos; i--) {
			word[i] = word[i-1];
		}
	}
	/* bebaiwsou oti exei '\0' sto telos  */
	word[WORDLENGTH-1] = '\0';
	
	/* antigrafi tou inset sti leksi, ksekinontas apo ekei pou einai i paula */
	for (i=0, j=dashpos; i<strlen(inset) && j<WORDLENGTH-1; i++, j++) {
		word[j]=inset[i];
	}
	printf("%s\n", word);
	return 0;
}
	
