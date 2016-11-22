#include<stdio.h>
#include<math.h>

int factorial(int n);
double eulerConstant(int limit);

int main(int argc, char *argv[]) {
	int limit;
	
	do {
		printf("Enter a non-negative integer: ");
		scanf("%d", &limit);
	} while (limit < 0);

	printf("%lf\n", log(eulerConstant(limit)));
	return 0;
}

/* calculates and returns the factorial of n */
int factorial(int n) {
	int i, product;
	product = n;
	for (i=n-1; i>=1; i--) {
		product *= i;
	}
	return product;
}

/* calculates and returns Euler's constant */
double eulerConstant(int limit) {
	double sum=1;
	int i;

	for (i=1; i<=limit; i++) {
		sum+=1.0/factorial(i);
	}
	return sum;
}
