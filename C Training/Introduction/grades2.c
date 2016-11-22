#include<stdio.h>

int main (int argc, char *argv[]) {

	char letter_grade;
	printf("Enter letter grade: ");
	scanf("%c", &letter_grade);

	switch (letter_grade) {
		case 'A':
		case 'a':
				  printf("Well done!\n");
				  break;
		case 'B':
		case 'b': printf("Good job!\n");
				  break;
		case 'C': 
		case 'c': printf("Not bad!\n");
				  break;
		case 'F':
		case 'f': printf("Try harder next time!\n");
				  break;
		default: printf("Error! Invalid grade.\n");
				 break;
	}
	return 0;
}
