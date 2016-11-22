/* apospasi ki ektupwsi twn psifiwn enos mi-arnitikou akeraiou me xrisi 
pinaka gia tin proswrini apothikeusi twn psifiwn. */

#include<stdio.h>

#define SIZE 10

int main (int argc, char *argv[]) {
	unsigned int number;

	int digits[SIZE], i;
	/* 
	Arxika gemizoume ton pinaka me -1. 
	An se mia thesi uparxei -1, tote thewroume oti auti den periexei
	egkuro psifio. 
	Enallaktika, tha mporousame na ti gemizoume me midenika.
	*/
	for (i=0; i<SIZE; i++) {
		digits[i] = -1;
	}

	printf("Enter a non-negative number: ");
	scanf("%u", &number);
	
	/* Eidiki periptwsi pou to number einai 0.
		Xreiazetai na to xeiristoume ksexwrista, giati to loop
		trexei mono gia number > 0 */
	if (number == 0) {
		printf("0\n");
		return 0;
	}

	int lastIndex = SIZE-1; /* kratame tin teleutaia adeia thesi tou pinaka */
	while (number > 0) {
		digits[lastIndex--] = number%10;
		number /= 10;
	}
	
	/* den ektupwnoume tis mi-egkures theseis */
	for (i=0; digits[i]==-1; i++);

	for (; i<SIZE; i++) {
		printf("%d ", digits[i]);
	}
	printf("\n");	

	return 0;
}

	
