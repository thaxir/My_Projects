#include <stdio.h>
#include <string.h>
#define N 30
#include <stdlib.h>

void replace (char *str1,char *str2,char *str3){
  char *p;
  
  p=strstr(str1,str2);
  if(p==NULL){
    return ;
  }
  else{
    strncpy(p,str3,strlen(str3));
  }
  replace(str1,str2,str3);
}



int main(int argc,char * argv[]){
  char *p1,*p2,*p3;
  
  p1=(char *)malloc(N*sizeof(char));
  p2=(char *)malloc(N*sizeof(char));
  p3=(char *)malloc(N*sizeof(char));
  
  printf("enter string \n");
  scanf("%s",p1);
  printf("enter string you ll get replaced\n");
  scanf("%s",p2);
  printf("enter string you ll replace with\n");
  scanf("%s",p3);
  
  replace(p1,p2,p3);
  printf("%s",p1);
  free(p1);
  free(p2);
  free(p3);
  return 0;
}