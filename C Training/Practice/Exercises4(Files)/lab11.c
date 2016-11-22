#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char * argv[]){
  
  FILE *f1,*f2,*f3;
  char c,c1,c2;
  int i;
  
  while(argc>4 || argc<0){
  printf("lathos arithmos orismatwn \n");
  }

  
  
  f2=fopen(argv[2],"r");
  if(f2==NULL){
    printf("arxeio dn vrethike\n");
    exit(1);
  }
  f3=fopen(argv[3],"w");
   if(f3==NULL){
    printf("Error \n");
    exit(1);
  }
  while(!feof(f2)){
    f1=fopen(argv[1],"r");
    if(f1==NULL){
      printf("arxeio dn vrethike\n");
      exit(1);
    }
    fscanf(f2," %c",&c)	;
    if(feof(f2)){
      break;
      
    }
    if(c==EOF){
      exit(1);
    }
    for(i=0,fscanf(f1," %c",&c1);(!feof(f1)) && c!=c1;i++,fscanf(f1," %c",&c1)); // mallon thelei pali elegxo edw  
										 
    fprintf(f3,"%c",'a'+i);
    fclose(f1);
  }
    
    fclose(f2);
    fflush(f3);
    fclose(f3);
    return 0;
}

      
    
  
  