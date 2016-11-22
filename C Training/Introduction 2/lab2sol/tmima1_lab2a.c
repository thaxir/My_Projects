/* Programma pou ektupwnei tin apodeiksi mias paraggelias kafe. */

/* Paratiriseis:

  - Onomata metablitwn
	Paratiriste oti olew oi metablites exoun perigrafika onomata.

  - Onomata statherwn
	Paratiriste oti o foros exei dilwthei ws stathera, me perigrafiko 
	onoma grammeno me kefalaia.

  - Timi forou. 
	Paratiriste oti to foro ton exoume grapsei ws 0.23. Enallaktika, tha
	mporousame na ton eixame arxikopoiisei ws 23.0/100 .
	Ena suxno lathos itan na tou anatethei i timi 23/100. Auto, ws diairesi
	anamesa se akeraious, exei tin timi 0 (to .23 kobetai) kai telika
	bgainoun lathos apotelesmata.

  - Formarisma eksodou.
	Theloume oi dekadikoi arithmoi na tupwthoun me toulaxiston 2 akeraia psifia
	kai 2 dekadika. Epomenws sto printf tha prosdiorisoume %5.2lf
	To 5 einai to sunoliko megethos tou arithmou (2 dekadika + 1 teleia + 2 akeraia)
	kai to 2 einai ta dekadika psifia.
*/

#include<stdio.h>

int main(int argc, char *argv[]) {

	int numCoffees; 
	double coffeePrice, tax, subtotal;

	const double TAXRATE = .23;

	printf("How many coffees? ");
	scanf("%d", &numCoffees);
	printf("Coffee price? ");
	scanf("%lf", &coffeePrice);

	subtotal = numCoffees*coffeePrice;
	tax = subtotal*TAXRATE;

	printf("C CAFE\n");
	printf("Coffee: %5.2lf\n", subtotal);
	printf("Tax:    %5.2lf\n", tax);
	printf("Total:  %5.2lf\n", subtotal+tax);

	return 0;
}
	
