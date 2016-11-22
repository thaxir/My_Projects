/* Programma pou diabazei tous bathmous 100 foititwn kai 
upologizei to plithos twn midenikwn kathws kai twn bathmwn 
sta diastimata (i, i+1] opou to i kumenetai apo 0 ews 9. 
*/

#include<stdio.h>
#include<math.h>
#define GRADERANGE 11    /* range is 0 throuth 10, inclusive */   
#define STUDENTS 10

int main (int argc, char *argv[]) {
	double grades[STUDENTS];
	int gradeRanges[GRADERANGE]; 

	int i;
	for (i=0; i<STUDENTS; i++) {
		scanf("%lf", &grades[i]);
	}

	for (i=0; i<GRADERANGE; i++) {
		gradeRanges[i] = 0;
	}

	for (i=0; i<STUDENTS; i++) {
		gradeRanges[(int)ceil(grades[i])]++;
	}
			
	for (i=0; i<GRADERANGE; i++) {
		printf("%d\n", gradeRanges[i]);
	}
	return 0;
}
	
