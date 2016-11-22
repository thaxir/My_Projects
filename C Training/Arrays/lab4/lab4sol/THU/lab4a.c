/* programma pou diabazei tous arithmous mitrwou kai bathmous
enos arithmou foititwn kai taksinomei tous arithmous mitrwou
wste osoi exoun probibasimo bathmo na emfanizontai prin apo 
autous pou exoun mi-probibasimo bathmo */

#include<stdio.h>
#define STUDENTS 100

int main (int argc, char *argv[]) {
	int reportedGrades[STUDENTS][2];
	int i;

	for (i=0; i<STUDENTS; i++) {
		scanf("%d %d", &reportedGrades[i][0], &reportedGrades[i][1]);
	}

	int partiallySorted[STUDENTS];
	int front=0, back=STUDENTS-1; /* indices of the last passing and first
									non-passing grade respectively */
	for (i=0; i<STUDENTS; i++) {
		if (reportedGrades[i][1] >= 5) {
			partiallySorted[front++] = reportedGrades[i][0];
		}
		else {
			partiallySorted[back--] = reportedGrades[i][0];
		}
	}

	for (i=0; i<STUDENTS; i++) {
		printf("%04d\n", partiallySorted[i]);
	}
		
	return 0;
}
