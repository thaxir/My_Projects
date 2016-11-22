#include <stdio.h>
#include <string.h>
#include  <stdlib.h>
#define N 100

char * find_part(char * str,char c){
  char *tel,*arx,*new;
 if (strchr(str,c)==NULL){
   exit(1);
 }
 else{
   arx=strchr(str,c)+1;
   tel=strrchr(str,c);
 }
 new =(char*)malloc ((tel-arx+1)*sizeof(char));
 strncpy(new,arx,tel-arx);
 return (new);
}
 
 

int main(int argc,char * argv[]){
  char * string,c,*new;
  
  string=(char *)malloc(N-1*sizeof(char));
  printf("Enter string: \n");
  scanf("%99s",string);
  printf("Enter a char : \n");
  scanf(" %c",&c);
  
  new=find_part(string,c);
  printf("string  %s \n",new);
  return 0;
}

  