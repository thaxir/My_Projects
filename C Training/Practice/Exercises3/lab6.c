#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define N 20

char * find_last(char *c,char del){
  char * pos;
  
  for(; *c!='\0';c++){
    if(*c==del){
      pos=c;
    }
  }

return pos;
}

char * reverse(char * str){
  int i,len;
  
  char*arxh,*telos,temp;
  
  len=strlen(str);
  
  arxh=str;
  telos=str;
  
  for(i=0;i!=len-1;i++){
    telos++;
  }
 
  if (len % 2==0){
    for(i=0; i<=len/2;i++){
      temp=*arxh;
      *arxh=*telos;
      *telos=temp;
      arxh++;
      telos--;
    }
  }
  if(len%2==1){
    for(i=0; i<len/2;i++){
      temp=*arxh;
      *arxh=*telos;
      *telos=temp;
      arxh++;
      telos--;
    }
  }
  return str;
}
int main(int argc, char * argv[]){
  int ep;
  char * c,* pos,*reversed;
  char del;
 
  do{
  printf("1. find last char \n2. reverse\n");
  scanf("%d",&ep);
  }while(ep!=1 && ep!=2 && !isdigit(ep));
  
  c=(char *)malloc(20*sizeof(char));
  switch (ep){
    case 1 :
      printf("Enter a string :\n");
      scanf("%19s",c);
      printf("Enter which char you want to find :\n");
      scanf(" %c",&del);
      pos=find_last(c,del);
      printf(" %s\n",pos);
      break;
    case 2 :
      printf("Enter a string you wanna reverse :\n");
      scanf("%19s",c);
      reversed=reverse(c);
      printf("%s\n",reversed);
      break;
      
  
  
  }
  return 0;
}