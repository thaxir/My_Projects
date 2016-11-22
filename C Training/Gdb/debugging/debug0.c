/* 
 * debug0.c
 * Author: Vana Doufexi
 * Date:   27/10/08
 * Description: To programma diabazei enan akeraio apo to standard input, ki 
				ektupwnei YES 'i NO analoga me to an einai artios 'i perittos.
 */

#include<stdio.h>

/* 
 * DEFINITIONS
 */

#define YES 1
#define NO 0

/* 
 * PROTOTYPES 
 */

int isEven (int num) ;


/* 
 * MAIN
 */ 
int main () {

	int arithmos;
	int apotelesma;

	printf("Dwste enan akeraio: ");
	scanf("%d", &arithmos);

	apotelesma = isEven(arithmos);

	if (apotelesma = YES) {
		printf("O %d einai artios.\n", arithmos);
	}
	else {
		printf("O %d einai perittos.\n", arithmos);
	}
	return 0;
}
	

/* isEven(num)
 * Perigrafi: Epistrefei 1 an o akeraios num einai artios, 0 diaforetika.
 * Eisodos: akeraios num
 * Eksodos: akeraios 0 (NO) 'i 1 (YES)
 */
int isEven (int num) {

	if (num % 2 == 0) {
		return YES;
	}
	else {
		return NO;
	}
}
