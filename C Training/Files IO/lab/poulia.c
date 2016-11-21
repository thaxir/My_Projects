#include <stdio.h>
#include <stdlib.h>

#define N 10

int main(int argc,char* argv[]){
  FILE * f1;
  FILE * f2;
  char c;
  int i,j;
  
  if(argc!=3){
    printf(" Incorrect number of arguments.\n");
    exit(1);
  }
  
  f1=fopen(argv[1],"r");
  
  if(f1==NULL){
    printf("Error opening file \"%s\"",argv[1]);
    exit(1);
  }
  
  f2=fopen(argv[2],"w");
  
  if(f2==NULL){
    printf("Error opening file \"%s\"",argv[2]);
    exit(1);
  }
  for(j=0;j<N ;j++){
    
    for(i=0;i<N;i++){
      c=fgetc(f1);
      fputc(c,f2);
      fseek(f2,N-1,SEEK_CUR);
      fputc(c,f2);
      fseek(f2,-N,SEEK_CUR);
    } 
  fgetc(f1);
  fseek(f2,N,SEEK_CUR);
  fputc('\n',f2);
  }
  fflush(f2);
  fclose(f2);
  fclose(f1);
  return 0;
}