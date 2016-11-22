#include<stdio.h>
#include<math.h>

#define PI 3.14159

double calcPi(int limit);
double calcPerimeter(double radius, double pi);

int main(int argc, char *argv[]) {

	double radius;
	int limit;

	printf("Enter limit: ");
	scanf("%d", &limit);

	printf("Enter radius: ");
	scanf("%lf", &radius);

	printf("%lf\n", calcPerimeter(radius, calcPi(limit)));
	return 0;
}


/* approximates  and returns the value of pi. 
If limit is non-positive, it returns a pre-defined value of pi */
double calcPi(int limit) {
	double sum = 0;
	int i;

	if (limit <= 0) {
		return PI;
	}
	
	for (i=1; i<=limit; i++) {
		sum+=1.0/pow(i, 2);
	}

	return sqrt(6*sum);
}
	

/* calculates and returns a circle's perimeter, given its radius and 
the value of pi to be used in the calculation */
double calcPerimeter(double radius, double pi) {

	return (2*pi*radius);
}
