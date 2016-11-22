/* Programma pou ulopoiei ton algorithmo 'counting sort'
gia na taksinomisei ena plithos arithmwn */

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

	/* taksinomisi */
	int sorted[SIZE], j;
	int last_pos=0; /* thesi gia ton epomeno arithmo pou prepei 
						na mpei ston taksinomimeno pinaka */
	for (i=0; i<MAXVAL+1; i++) {
		for (j=last_pos; j<last_pos+occurrences[i]; j++) {
			sorted[j]=i;
		}
		last_pos = j;
	}
		
	/* ektupwsi taksinomimenou pinaka  */
	for (i=0; i<SIZE; i++) {
		printf("%d\n", sorted[i]);
	}
	return 0;
}
