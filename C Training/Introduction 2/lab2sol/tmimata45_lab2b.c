/* reverse the digits of a 3-digit number */

#include<stdio.h>

int main () {
	int number, reversed;

	printf("Enter number: ");
	scanf("%d", &number);

	int digit1 = number/100;
	number = number%100;

	int digit2 = number/10;
	number = number%10;

	int digit3 = number;

	reversed = digit3*100+digit2*10+digit1;

	printf("The number reversed is %d\n", reversed);

	return 0;
}
