/* metatropi posou se arithmo apo galleons, sickles kai knuts */

#include<stdio.h>

int main (int argc, char *argv[]) {
	int amount;
	printf("Enter amount: ");
	scanf("%d", &amount);

	int galleons, sickles, knuts;
	knuts = amount%29;
	amount = amount/29;
	sickles = amount%17;
	galleons = amount/17;

	printf("%d %d %d\n", galleons, sickles, knuts);
	return 0;
}
