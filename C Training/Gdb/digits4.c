/* 
Parallagi tou digits3.c
O upologismos tou plithous psifiwn ginetai me metrima. 
*/
#include<stdio.h>
#include<math.h>

int main () {
	int number, digit, power;
	printf("Enter number: ");
	scanf("%d", &number);
	if (number < 0) {
		printf("Positive numbers only\n");
		return 1;
	}

	int num_digits = 0;
	int num_copy = number; /* ftiaxnoume antigrafo tou arithmou, to opoio
							tha katastrafei */
	while (num_copy > 0) {
		num_copy /= 10;
		num_digits++;
	}

	while (num_digits > 0) {
	
		power = pow(10, --num_digits);
		digit = number / power;
		number = number % power;
		printf("%d ", digit);
	}
	printf("\n");
	return 0;
}
