#include<stdio.h>

int main () {
	char calendar = 0;
	calendar = 1;  // 0000 0001
	calendar <<=2; // 0000 0100
	calendar++;    // 0000 0101
	calendar <<=2; // 0001 0100
	calendar++;    // 0001 0101
	calendar <<=2; // 0101 0100
	printf("%x\n", calendar);
	char mask = ~0; // mask: 1111 1111
	printf("%x\n", mask);
	calendar ^=mask;  // calendar: 1010 1011. Idio me tin praksi: calendar = ~calendar
	printf("%x\n", calendar);
	return 0;
}
	
