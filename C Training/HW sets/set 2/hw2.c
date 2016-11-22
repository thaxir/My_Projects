#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 1
#define MOTO 1.25
#define CAR 2.35
#define BUS 16.50
#define TRUCK 8.40
#define END 0

void amaksia(char oxhma[][11],float plhrwmes[]){
  int i,j;
  char c;
  float poso,diafora;
  
  for(i=0,j=0;i<1;i++){
    printf("vale pinakides (2h3) kai space \n");
    scanf("%4s",&oxhma[i][j]);
    printf("vale arithmo pinakidas 4psifia kai keno \n");
    scanf("%5s",&oxhma[i][j+4]);
    printf("vale typo oxhmatos \n");
    scanf(" %c",&c);
    if(isupper(c)){
      oxhma[i][9]=c;
    }
    else{
      c-='a'-'A';
      oxhma[i][9]=c;
    }
    oxhma[i][10]='\0';
    switch (c){
      case 'C' :
	printf("PAY \"%.2f\"\n>",CAR);
	scanf("%f",&poso);
	if(poso<CAR){
	  diafora=CAR-poso;
	  plhrwmes[i]=diafora;
	}
	else{
	  plhrwmes[i]=0.0;
	}
	break;
      case 'T' :
	printf("PAY \"%.2f\"\n> ",TRUCK);
	scanf("%f",&poso);
	if(poso<TRUCK){
	  diafora=TRUCK-poso;
	  plhrwmes[i]=diafora;
	}
	else{
	  plhrwmes[i]=0.0;
	}
	break;
      case 'B' :
	printf("PAY \"%.2f\"\n> ",BUS);
	scanf("%f",&poso);
	if(poso<BUS){
	  diafora=BUS-poso;
	  plhrwmes[i]=diafora;
	}
	else{
	  plhrwmes[i]=0.0;
	}
	break;
      case 'M' :
	printf("PAY \"%.2f\"\n> ",MOTO);
	scanf("%f",&poso);
	if(poso<MOTO){
	  diafora=MOTO-poso;
	  plhrwmes[i]=diafora;
	}
	else{
	  plhrwmes[i]=0.0;
	}
	break;
    }
    printf("vale poso pou dwthike\n");
    
  }
  for(i=0;i<N;i++){
    printf("edw exoume auto : %s\n",oxhma[i]);
  }
}
 
int main(int argc,char * argv[]){
  char oxhma [N][11];
  float plhrwmes[N];
  int arithmos;
  
  while(1){
    printf("Dwse arithmo oxhmatwn \n");
    scanf("%d",&arithmos);
    if(arithmos==END){
      break;
    }
  }
  amaksia(oxhma,plhrwmes);
  return 0;
}
  
  