#include<stdio.h>
#include <string.h>

int main(int argc, char * argv[]){
  FILE * f_desc;
  char str[64];
  
  f_desc=fopen(argv[1],"w");
  if(f_desc==NULL){
    return 1;
  }
  do{
    scanf("%63s",str);
    fprintf(f_desc,"%s ",str);
  }while(strcmp(str,"end"));
  fflush(f_desc);
  fclose(f_desc);
  
  f_desc=fopen(argv[1],"r");
  while(1){
    fscanf(f_desc,"%63s",str);
    if(feof(f_desc)){
      break;
    }
    printf("%s ",str);
  }
  fclose(f_desc);
  return 0;
}
  
  