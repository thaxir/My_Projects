#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 50



void find(char *str,char word[],char word1[]){
  char *p,*g;
  
 if(strlen(word1)==strlen(word)){
    while((p=strstr(str,word))!=NULL){
    
      strncpy(p,word1,strlen(word));
    }
  }
  else
    while((p=strstr(str,word))!=NULL){
     strncpy(p,word1,strlen(word));
      g=p+strlen(word);
     strcat(p,g);
    }
}

int main(int argc,char *argv[]){
  char *str;
  char word[N],word1[N];
  
  str=(char*)malloc(N*sizeof(char));
   
  
  printf("enter a string \n");
  scanf("%s",str);
  
  printf("enter a string \n");
  scanf("%s",word);
  
  printf("Enter a string \n");
  scanf("%s",word1);
  
  if(strlen(word1)>strlen(word)){
    printf("word error\n");
    return 1;
  }
  
  find(str,word,word1);
  printf("new string is : %s",str);
  return 0;
}
  