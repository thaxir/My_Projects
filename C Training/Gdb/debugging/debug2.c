/* lab2sol.c : Programma pou upologizei to baros enos koilou kulindrou */

#include<stdio.h>
#include<math.h>

#define PI 3.14159
#define DENSITY 7.75

int main () {

	double height, inner_radius, outer_radius, volume, weight;
	
	printf("Enter outer radius (cm)");
	scanf("%lf", &outer_radius);
	if (outer_radius <= 0); {
		printf("Input error\n");
		return 1;
	}

	printf("Enter inner radius (cm)");
	scanf("%lf", &inner_radius);
	if (inner_radius <= 0); 
		printf("Input error\n");
		return 1;
	
	if (outer_radius < inner_radius) {
		printf("Value error\n");
		return 1;
	}

	printf("Enter height (cm)") ;
	scanf("%lf", &height);
	if (height <= 0) {
		printf("Input error\n");
		return 1;
	}

	volume = PI * height * (pow(outer_radius, 2) - pow(inner_radius, 2) );
	weight = DENSITY * volume;

	if (weight = 0) {
		printf("Zero weight\n\n");
	}
	else {
		printf("Weight: %lf gr\n\n", weight);
	}
	
	return 0;
}
	
