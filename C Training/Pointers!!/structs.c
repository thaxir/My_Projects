#include<stdio.h>
#include<string.h>

#define NAMESIZE 20
#define NUMSTUDENTS 3

typedef enum {PRWTOETIS=1, MEGALOETIS} studentT;


typedef struct {
	studentT category;
	char name[NAMESIZE];
	union {
		char lab[5];
		double project;
	} grade;
} studentInfoT;

int main (int argc, char *argv[]) {
	int i, category;

	studentInfoT class[NUMSTUDENTS];

	char formatstring[15];
	sprintf(formatstring, "%%%ds", NAMESIZE-1);

	for (i=0; i<NUMSTUDENTS; i++) {
		printf("Enter %d for junior, %d for other: ", PRWTOETIS, MEGALOETIS);
		scanf("%d", &category);
		class[i].category = (studentT) category;
		printf("Enter name: ");
		scanf(formatstring, class[i].name);
		switch(class[i].category) {
			case PRWTOETIS: 
				printf("Enter lab grade: ");
				scanf("%4s", class[i].grade.lab);
				break;
			case MEGALOETIS:
				printf("Enter project grade: ");
				scanf("%lf", &class[i].grade.project);
				break;
		}
	}

	for (i=0; i<NUMSTUDENTS; i++) {
		printf("%s, ", class[i].name);
		switch(class[i].category) {
			case PRWTOETIS: printf("Prwtoetis, lab: %s\n", class[i].grade.lab);
							break;
			case MEGALOETIS: printf("Megaloetis, project: %.2lf\n", class[i].grade.project);
							break;
		}
	}
	return 0;
}
