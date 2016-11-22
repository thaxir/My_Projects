#define ARRAY_LEN	45
#include <stdio.h>
int howmany(int array[],int digit,int fores,int i,int synolo){
 
  if(i!=synolo){
    
    if(array[i]==digit){
      return (howmany(array,digit,fores+1,i+1,synolo));
    }
    else{
      return (howmany(array,digit,fores,i+1,synolo));

    }
  }
  else return fores;
}
  

int main(void) {
   int array[] = {9,8,7,6,5,4,3,2,1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,
                   3,4,5,6,7,8,9,9,8,7,6,5,6,7,8,9,9,8,7,8,9,9};
   int digit;
   
    printf("vale psifio pou thes na psaksei\n");
    scanf("%d",&digit);
    digit=howmany(array,digit,0,0,45);
    printf("to psifio pou thes yparxei %d fores\n",digit);
    return 0;
    
}