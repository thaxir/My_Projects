#include<stdio.h>
#include<math.h>

#define GRAVITY_ACCELERATION 9.8
#define VALID 1
#define INVALID 0

int checkInput(double height, double time);
double calcTimeToFall(double distance);

int main (int argc, char *argv[]) {
	
	double height;
	int timeToEat;
	double timeToFall;

	printf("Cliff height: ");
	scanf("%lf", &height); 
	printf("Time to eat: ");
	scanf("%d", &timeToEat);

	while (checkInput(height, timeToEat) == INVALID) {
		printf("Incorrect input, try again.\n");
		printf("Cliff height: ");
		scanf("%lf", &height); 
		printf("Time to eat: ");
		scanf("%d", &timeToEat);
	}

	timeToFall = calcTimeToFall(height);
	if (timeToEat < timeToFall) {
		printf("The roadrunner escapes\n");
	}
	else {
		printf("The coyote enjoys dinner\n");
	}
	return 0;
}
	
/* epistrefei VALID an kai oi duo parametroi einai thetikes, diaforetika
epistrefei INVALID  */
int checkInput(double height, double time) {
	if (height > 0 && time > 0) {
		return VALID;
	}
	else {
		return INVALID;
	}
}

/* Ypologizei ki epistrefei to xrono pou kanei na pesei ena 
	antikeimeno apo upsos distance */
double calcTimeToFall(double distance) {
	return sqrt(2 * distance / GRAVITY_ACCELERATION);
}
