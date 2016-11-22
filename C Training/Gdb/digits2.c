/* apospasi ki ektupwsi twn psifiwn enos mi-arnitikou akeraiou me xrisi 
logarithmwn gia tin euresi tou plithous psifiwn tou arithmou.
PROSOXI: O algorithmos de leitourgei gia pollaplasia tou 10 */

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
	while (number >= 10) {
	
		power = pow(10, floor(log10(number)));
		digit = number / power;
		number = number % power;
		printf("%d ", digit);
	}
	printf("%d\n", number); /* to teleutaio psifio */
	return 0;
}
