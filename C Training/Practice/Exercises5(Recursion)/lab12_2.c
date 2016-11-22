#include <stdio.h>
#include <stdlib.h>

void asteria(int n,int i){
  
  if(n==0){
    return;
  }
  else{
    printf("%* *\n",i);
   
  }
  asteria(n-1,i+1);
}
  


int main(int argc,char * argv[]){
  
  int n;
  int i=0;
  n=atoi(argv[1]);
  if(n<0){
    exit(0);
  }
  else{
    asteria(n,i);
  }
  return 0;
  
}