#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define SIZE 39



struct workerT{
  int arx;
  int tel;
  char name[SIZE];
};


struct workerT getshift(char *c){
  char *d;
  struct workerT str;
  int n,r;
  
  d=strchr(c,'-');
  n=strlen(d);
  strncpy(str.name,c,n);
  r= atoi(c);
  str.arx= r;
  str.tel=r+8;
  printf("%s ,arxh %d,telos %d\n ",str.name,str.arx,str.tel);
  return (str);
  
}
  
  
  

int main (int argc, char * argv[]){
  char c[SIZE];
  struct workerT p;
  
    printf("Enter data : \n");
    scanf("%s",c);
    
   p=getshift(c);
    
  
return 0;

}