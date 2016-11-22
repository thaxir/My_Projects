/* programma antistoixisis arithmitikou bathmou se gramma.
90-100: A
80-89 : B
65-79: C
0 -64 : F
*/

#include<stdio.h>

int main (int argc, char *argv[]) {

	int num_grade;

	do {
		printf("Enter grade (0-100): ");
		scanf("%d", &num_grade);
	} while (num_grade < 0 || num_grade > 100);

	if (num_grade >= 90 && num_grade <= 100) {
		printf("A\n");
	}
	else if (num_grade >= 80 && num_grade < 90) {
		printf("B\n");
	}
	else if (num_grade >= 65 && num_grade < 80) {
		printf("C\n");
	}
	else if (num_grade >=0 && num_grade < 65) {
		printf("F\n");
	}
	else {
		printf("Error: Invalid grade!\n");
	}

	return 0;
}
