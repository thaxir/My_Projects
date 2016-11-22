#include <stdio.h>
#include <stdlib.h>



int vres(int l){
  int modulo;
  
  if(l==0)return 0;
  if(l<0){
    
    l=-l;
  }
  while(l>0){
    modulo=l%10;
    if(modulo!=1){
      
    return 0;
  }
  else
    l=l/10;
  }
  return 1;
}

int main(int argc,char *argv[]){
  FILE *f1;
  int l;
  
  f1=fopen(argv[1],"r");
  if(f1==NULL){
    printf("File not found\n");
    exit(1);
  }
  while(!feof(f1)){
    fscanf(f1,"%d",&l);
    l=vres(l);
    printf("%d\n",l);
  }
  return 0;
}
    
    
    