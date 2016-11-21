#include <stdio.h>

int main (int argc, char * argv[]){
  FILE *f_desc;
  char c;
  f_desc = fopen(argv[1],"w");
  if(f_desc==NULL){
    return(1);
  }
  do{
    c=getchar();
    fputc(c,f_desc);
  }while(c!='~');
  fflush(f_desc);
  fclose(f_desc);
  
  f_desc=fopen(argv[1],"r");
  while (1){
    c=fgetc(f_desc);
    if(feof(f_desc)){
      break;
    }
    putchar(c);
  }
  fclose(f_desc);
  return 0;
}