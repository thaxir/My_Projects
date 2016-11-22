/* separates and prints the digits of an integer with up to five digits */

/* Paratiriseis:
	- Paratiriste pws i diadikasia gia kathe psifio einai akribws idia.
	Diairoume me dunami tou 10 kai meta pairnoume to upoloipo tis diairesis
	me dunami tou 10. Me ligi skepsi, mporoume na broume tropo na grapsoume 
	to programma mas etsi wste na xrisimopoiei mia domi epanalipsis gia na kanei
	auti ti leitourgia. Skeftite to!
*/

#include<stdio.h>

int main () {
	int number, digit1, digit2, digit3, digit4, digit5;
	printf("Enter number: ");
	scanf("%d", &number);
	digit1 = number/10000;
	number = number%10000;
	digit2 = number/1000;
	number = number%1000;
	digit3 = number/100;
	number = number%100;
	digit4 = number/10;
	number = number%10;
	digit5 = number;
	printf("%d %d %d %d %d\n", digit1, digit2, digit3, digit4, digit5);
	return 0;
}
