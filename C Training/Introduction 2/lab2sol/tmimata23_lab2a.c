/* Programma pou ektupwnei tin apodeiksi enos benzinadikou */

#include<stdio.h>

/* Paratiriseis:

  - Onomata metablitwn
    Paratiriste oti olew oi metablites exoun perigrafika onomata.

  - Onomata statherwn
    Paratiriste oti oi times ana litro exoun dilwthei ws statheres, me perigrafika
    onomata grammena me kefalaia.

  - Pososta (2/3, 1/3)
    Paratiriste oti ta pososta ta exoume grapsei ws 2.0/3.0 kai oxi ws 2/3.
    To 2/3 kanei diairesi anamesa se akeraious, opote to apotelesma prepei na einai
	akeraios, kai kata sunepeia einai 0 (to .66 kobetai). 

  - Formarisma eksodou.
    Theloume oi dekadikoi arithmoi na tupwthoun me toulaxiston 3 akeraia psifia
    kai 2 dekadika. Epomenws sto printf tha prosdiorisoume %6.2lf
    To 6 einai to sunoliko megethos tou arithmou (2 dekadika + 1 teleia + 3 akeraia)
    kai to 2 einai ta dekadika psifia.
*/

int main (int argc, char *argv[]) {

	const double INIT_PRICE = 1.64;
	const double EXTRA_PRICE = 1.32;
	int liters; /* i ekfwnisi den prosdiorizei tupo, ginontai dekta int kai double */

	printf("How many liters? ");
	scanf("%d", &liters);

	double two_thirds_price = liters*(2./3.)*INIT_PRICE;
	double one_third_price = liters*(1./3)*EXTRA_PRICE;

	printf("C GAS\n");
	printf("Gas (2/3): %6.2lf\n", two_thirds_price);
	printf("Gas (1/3): %6.2lf\n", one_third_price);
	printf("Total:     %6.2lf\n", two_thirds_price + one_third_price);
	return 0;
}        
