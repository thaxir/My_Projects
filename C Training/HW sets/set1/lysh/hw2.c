#include <stdio.h>
#include <ctype.h>
#define MOTO 1.25
#define CAR 2.35
#define BUS 16.50
#define TRUCK 8.40
#define END 0

void resta(float poso){
  
  int ypoloipo=0;
  
  printf("changes are : \n \n");
  if((poso/20.0)>=1){
    printf("%d of 20 euro\n",ypoloipo=(int)poso/20);
    poso-=(ypoloipo*20.0);
  }
  if((poso/5.0) >=1 ){
    printf("%d of 5 euro \n",ypoloipo=(int)poso/5);
    poso-=(ypoloipo*5.0);
  }
   if((poso/1.0) >=1 ){
    printf("%d of 1 euro \n",ypoloipo=(int)poso/1);
    poso-=(ypoloipo*1.0);
  }
     if((poso*10) >=1 ){
    printf("%d of 10 cents \n",ypoloipo=poso*10);
    poso-=(ypoloipo*0.1);
     }
     if((poso*100) >=1 ){
    printf("%d cents \n",ypoloipo=poso*100);
    poso-=(ypoloipo*0.01);
     }
  
  
}





void plhrwma(char oxhma){
  
  float poso=0.0;
  float poso1=0.0;
  float diafora=0.0;
  
    switch(oxhma){
    case 'C' :
      printf("PAY \"%.2f\"\n>",CAR);
      scanf("%f",&poso);
      if(poso<CAR){
	
	diafora=CAR-poso;
	while(diafora > 0.0){
	  printf("PAY \"%2.2f\" more \n>",diafora);
	  scanf("%f",&poso1);
	  diafora-=poso1;
	}
      }
      if(poso>CAR){
	poso-=CAR ;
	resta(poso);
	  
      }
      break;
    case 'M' :
	printf("PAY \"%.2f\"\n> ",MOTO);
	scanf("%f",&poso);
	if(poso<MOTO){
	  diafora=MOTO-poso;
	  while(diafora > 0.0){
	    printf("PAY \"%2.2f\" more \n>",diafora);
	    scanf("%f",&poso1);
	    diafora-=poso1;
	  }
	}
	if(poso>MOTO){
	  poso-=MOTO;
	  resta(poso);
	}
	break;
    case 'T' :
	printf("PAY \"%.2f\"\n> ",TRUCK);
	scanf("%f",&poso);
	if(poso<TRUCK){
	  diafora=TRUCK-poso;
	  while(diafora > 0.0){
	    printf("PAY \"%2.2f\" more \n>",diafora);
	    scanf("%f",&poso1);
	    diafora-=poso1;
	  }
	}
	if(poso>TRUCK){
	  poso-=TRUCK;
	  resta(poso);
	}
	break;
    case 'B' :
      printf("PAY \"%.2f\"\n> ",BUS);
      scanf("%f",&poso);
	if(poso<BUS){
	  diafora=BUS-poso;
	  while(diafora > 0.0){
	    printf("PAY \"%2.2f\" more \n>",diafora);
	    scanf("%f",&poso1);
	    diafora-=poso1;
	  }
	}
	if(poso>BUS){
	  poso-=BUS;
	  resta(poso);
	}
      break;
  }
}
  
int main (int argc,char *argv[]){
  
  char oxhma;
  int arithmos,i=0,c=0,m=0,t=0,b=0;
  float sum;
  while(1){
    printf("Dwse arithmo oxhmatwn \n");
    scanf("%d",&arithmos);
    if(arithmos==END){
      break;
    }
    else
      i++;
      do{
	printf("Enter vehicle type: \n");
	scanf(" %c",&oxhma);
      }while(oxhma!='C' && oxhma!='M' && oxhma !='B' && oxhma !='T');
    if(oxhma=='C')
      c++;
    if(oxhma=='M')
      m++;
    if(oxhma=='B')
      b++;
    if(oxhma=='T')
      t++;
    
     plhrwma(oxhma);
   }
   sum=m*MOTO+c*CAR+b*BUS+t*TRUCK;
   printf("Number of vechicles: %d \n Motorcycles: %f \n Cars: %f \n Buses: %f \n Trucks: %f \n Total: %f \n",i,m*MOTO,c*CAR,b*BUS,t*TRUCK,sum);

  return 0;
}


  
  
  
  
  
  
  
  


