/* Ypologizei to poso pou ofeilei ena autokinito se ena parking 
ki ektupwnei tin apodeiksi */
#include<stdio.h>

int main (int argc, char *argv[] ) {
	int hour_in, hour_out, minute_in, minute_out;
	int total_hour, total_minute;
	char type;
	const double CAR_RATE = 1.00;
	const double TRUCK_RATE = 1.50;
	const double MOTO_RATE = 0.50;

	double total_price;

	do {
		printf("Vehicle type: ");
		scanf(" %c", &type);
	} while (type != 'C' && type != 'M' && type != 'T');
	
	printf("Time entered: ");
	scanf("%d:%d", &hour_in, &minute_in);
	printf("Time left: ");
	scanf("%d:%d", &hour_out, &minute_out);

	if (minute_out < minute_in) {
		minute_out+=60;
		hour_out--;
	}
	total_hour = hour_out - hour_in;
	total_minute = minute_out - minute_in;
	
	switch (type) {
		case 'M': total_price = MOTO_RATE*(total_hour + total_minute/60.0);
				  break;
		case 'C': total_price = CAR_RATE*(total_hour + total_minute/60.0);
				  break;
		case 'T': total_price = TRUCK_RATE*(total_hour + total_minute/60.0);
				  break;
	}
	printf("\nC PARKING\n");
	printf("Vehicle type: %c\n", type);
	printf("Total time:   %02d:%02d\n", total_hour, total_minute);
	printf("PAY:          Euro %6.2lf\n", total_price);
	return 0;
}
