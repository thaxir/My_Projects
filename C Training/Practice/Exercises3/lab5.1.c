#include <stdio.h>

char *words(char pinakas [][10]){
  char *p;
  int i;
  p=&pinakas[0][0];
  for(i=0;i<2;i++){
    printf("vale name \n");
    scanf("%9s\n",&pinakas[i][0]);
  }
  return p;
}

int main(int arc,char * argv[]){
  char onoma[2][10];
  char *c;
   
  c=words(onoma);
  printf("%s\n",c);
  return 0;
}