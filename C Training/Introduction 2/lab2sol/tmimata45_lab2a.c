/* Programma pou ektupwnei tin apodeiksi apo tin egkatastasi moketas se ena dwmatio */

/* Paratiriseis:

  - Onomata metablitwn
    Paratiriste oti olew oi metablites exoun perigrafika onomata.

  - Onomata statherwn
    Paratiriste oti o foros exei dilwthei ws stathera, me perigrafiko 
    onoma grammeno me kefalaia. Omoiws i timi ana tetragwniko metro.

  - Timi forou. 
    Paratiriste oti to foro ton exoume grapsei ws 0.23. Enallaktika, tha
    mporousame na ton eixame arxikopoiisei ws 23.0/100 .
    Ena suxno lathos itan na tou anatethei i timi 23/100. Auto, ws diairesi
    anamesa se akeraious, exei tin timi 0 (to .23 kobetai) kai telika
    bgainoun lathos apotelesmata.

  - Formarisma eksodou.
    Theloume oi dekadikoi arithmoi na tupwthoun me toulaxiston 3 akeraia psifia
    kai 2 dekadika. Epomenws sto printf tha prosdiorisoume %6.2lf
    To 6 einai to sunoliko megethos tou arithmou (2 dekadika + 1 teleia + 3 akeraia)
    kai to 2 einai ta dekadika psifia.
*/

#include<stdio.h>

int main(int argc, char *argv[]) {

	double width, length, subtotal, tax;
	const double TAXRATE = .23;
	const double PRICE = 33;

	printf("Enter length: ");
	scanf("%lf", &length);
	printf("Enter width: ");
	scanf("%lf", &width);

	subtotal = length*width*PRICE;
	tax = subtotal*TAXRATE;

	printf("CARPET C\n");
	printf("Carpet: %6.2lf\n", subtotal);
	printf("Tax:    %6.2lf\n", tax);
	printf("Total:  %6.2lf\n", subtotal+tax);
	return 0;
}
	
