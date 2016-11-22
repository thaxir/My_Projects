#include<stdio.h>
#include<math.h>

#define GRAVITY_ACCELERATION 9.8
#define SPLIT_SECOND 0.1
#define ROADRUNNER_SPEED 32.18

double calcTimeToFall(double distance);
double calcTimeToTravel(double distance);

int main (int argc, char *argv[]) {
	
	double height, distance;
	double timeToTravel, timeToFall;

	printf("Cliff height: ");
	scanf("%lf", &height); 
	printf("Roadrunner distance: ");
	scanf("%lf", &distance);

	timeToFall = calcTimeToFall(height);
	timeToTravel = calcTimeToTravel(distance);

	if (fabs(timeToTravel - timeToFall) < SPLIT_SECOND) {
		printf("SPLAT!\n");
	}
	else {
		printf("ZOOM!\n");
	}
	return 0;
}
	
/* Ypologizei ki epistrefei to xrono pou kanei na pesei ena 
	antikeimeno apo upsos distance */
double calcTimeToFall(double distance) {
	return sqrt(2 * distance / GRAVITY_ACCELERATION);
}

/* Ypologizei ki epistrefei to xrono pou kanei ena beep-beep na  
	dianusei tin apostasi distance. */
double calcTimeToTravel(double distance) {
	double speed, time;

	speed = ROADRUNNER_SPEED * 1000/3600; /* convert to m/sec */
	time = distance / speed;
	return time;
}
