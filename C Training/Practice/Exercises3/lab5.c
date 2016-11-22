#include <stdio.h>
#include <string.h>

void word(char onomata[][10]){
  int i;
  for(i=0;i<3;i++){
  printf("dwse ena onoma : \n");
  scanf("%9s",onomata[i]);
  }
}
void find_longest(char onomata[][10]){
  int i;
  int mhkos=0;
  char *p;
    
  for(i=0;i<3;i++){
      if(mhkos<strlen(onomata[i])){
	mhkos=strlen(onomata[i]);
	p=onomata[i];
      }
    }
    printf("to megalytero mhkos einia %d kai to xei o %s  \n",mhkos,p);
}
  


void main (int argc,char * argv []){
  
  char onomata [3][10];

  
  word(onomata);
  find_longest(onomata);
  
}