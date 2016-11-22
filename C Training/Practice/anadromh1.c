#include <stdio.h>
void reverse(char str1[]){
  
  if(*str1=='\0')return;
  reverse(str1+1);
  printf("%c",*str1);
}
  


int main (int argc,char *argv[]){
  char str1[21];
  
  printf("enter a string \n");
  scanf("%s",str1);
  reverse(str1);
  printf("%s\n",str1);
}