/* Programma pou diabazei tis sxetikes theseis enos kunigou ki 
enos thiramatos kai anixneuei an o kunigos tha piasei to thirama */

#include<stdio.h>

int main (int argc, char *argv[]) {
	const double COYOTE_SPEED = 69.20; /* km/h */
	const double COUGAR_SPEED = 48.28; /* km/h */
	const double CHEETAH_SPEED = 112.65; /* km/h */
	const double ROADRUNNER_SPEED = 32.18; /* km/h */

	int hour, minute;
	double total_time;
	char predator;
	double init_distance, predator_distance, prey_distance, distance_diff;
	
	do {
		printf("Hunter: ");
		scanf(" %c", &predator);
	} while (predator != 'T' && predator != 'R' && predator != 'H');

	printf("Initial distance: ");
	scanf ("%lf", &init_distance);
	init_distance /=1000.0; /* convert to km */
		
	printf("Enter time: ");
	scanf("%d:%d", &hour, &minute);

	total_time = hour + minute/60.0;

	switch(predator) {
		case 'T': predator_distance = total_time * COYOTE_SPEED ;
				  break;
		case 'R': predator_distance = total_time * COUGAR_SPEED ;
				  break;
		case 'H': predator_distance = total_time * CHEETAH_SPEED ;
				  break;
	}
	prey_distance = total_time *  ROADRUNNER_SPEED;
	distance_diff = predator_distance + init_distance - prey_distance;

	printf("\nHunter        %5c\n", predator);
	printf("Distance diff %5.2lf\n", distance_diff);
	printf("Result        ");
	if (distance_diff >= 0 ) {
		printf("Munch Munch\n");
	}
	else {
		printf("Pant Pant\n");
	}
	return 0;
}
