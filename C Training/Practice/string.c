#include <stdio.h>
#include <stdlib.h>

void copy(char *str1,char*str2,int n){
  int i;
  
  for(i=0;i<=n-1;i++){
    *str1=*str2;
    ++str1;
    ++str2;
  }
  *str1='\0';
}


int main(int argc,char *argv[]){
  
  char *str1,*str2;
  
  str1=(char*)malloc(20*sizeof(char));
  str2=(char*)malloc(20*sizeof(char));
  
  printf("dwse string1 \n");
  scanf("%s",str1);
  printf("dwse string \n");
  scanf("%s",str2);
  printf("str1 einai : %s\nstr2 einai : %s\n",str1,str2);
  copy(str1,str2,6);
  printf("str1 einai : %s\nstr2 einai : %s\n",str1,str2);

  return  0;
}