/* programma pou briskei tin antistoixia anamesa se arithmitikous bathmous kai 
stin klimaka A, B, C, F */

#include<stdio.h>
int main(int argc, char *argv[]) {

	int grade;

	do {
		printf("Enter grade (0-100): ");
		scanf("%d", &grade);
	} while (grade >= 0 || grade <= 100);

	if (grade >= 90) {
		printf("A\n");
	}
	else if (grade >= 80) {
		printf("B\n");
	}
	else if (grade >= 70) {
		printf("C\n");
	}
	else {
		printf("F\n");
	}
	return 0;
}
	
	
