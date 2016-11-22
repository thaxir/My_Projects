#include <stdio.h>
#include <ctype.h>


int main (int argc,char *argv[]){
  const float MOTO=1.25;
  const float CAR=2.35;
  const float BUS=16.50;
  const float TRUCK=8.40;
  
  char oxhma;
  
  do{
    printf("Enter vehicle type: \n");
    scanf(" %c",&oxhma);
  }while(oxhma!='C' && oxhma!='M' && oxhma !='B' && oxhma !='T');
  
  switch(oxhma){
    case 'C' :
      printf("PAY \"%2.2f\"\n>",CAR);
      break;
    case 'M' :
	printf("PAY \"%2.2f\"\n> ",MOTO);
	break;
    case 'T' :
	printf("PAY \"%2.2f\"\n> ",TRUCK);
	break;
    case 'B' :
      printf("PAY \"%2.2f\"\n> ",BUS);
      break;
  }
  return 0;
}


  
  
  
  
  
  
  
  


