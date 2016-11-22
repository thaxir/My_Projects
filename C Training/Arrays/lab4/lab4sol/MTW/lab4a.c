/* Programma pou diabazei ena arithmo akeraiwn eurous 0 ews MAXVAL
kai upologizei ki ektupwnei to plithos emfanisewn tou kathenos */

#include<stdio.h>

#define SIZE 100
#define MAXVAL 20

int main (int argc, char *argv[]) {
	int numbers[SIZE];
	int occurrences[MAXVAL+1];
	int i;
	
	/* eisagwgi arithmwn */
	for (i=0; i<SIZE; i++) {
		scanf("%d", &numbers[i]);
	}
	
	/* arxikopoiisi deuterou pinaka */
	for (i=0; i<MAXVAL+1; i++) {
		occurrences[i] = 0;
	}

	/* metrima emfanisewn */
	for (i=0; i<SIZE; i++) {
		occurrences[ numbers[i] ]++;
	}

	/* ektupwsi emfanisewn */
	for (i=0; i<MAXVAL+1; i++) {
		printf("%d\n", occurrences[i]);
	}
	return 0;
}
