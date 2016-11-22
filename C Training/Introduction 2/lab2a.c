#include <stdio.h>

int main (int argc,char * argv[]){
  
  int cof=0;
  float price=0.0,foros=0.23,synolo=0.0;
  printf("How many coffees ?");
  scanf("%d",&cof);
  printf("Coffee price ?");
  scanf("%g",&price);
  price=price*cof;
  synolo=price+foros*price;
  printf("coffee : %2d \n tax : %40.2g \n ",cof,foros);
  printf("synolo einia : %3.2g\n",synolo);
 return 0;
}