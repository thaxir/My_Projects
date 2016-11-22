/* Diorthwsi tou digits2.c
O upologismos tou plithous psifiwn ginetai kai pali me logarithmous,
alla eksw apo to loop.
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

	int num_digits = floor(log10(number));
	while (num_digits >= 0) {
	
		power = pow(10, num_digits--);
		digit = number / power;
		number = number % power;
		printf("%d ", digit);
	}
	printf("\n");
	return 0;
}
