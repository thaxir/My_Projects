#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 100
#define MEGETHOS 10

typedef struct thanos {
  char * d;
  int len;
}infoT;

infoT * words[MEGETHOS];

void init_1(void){
  int i;
  
  for(i=0; i<MEGETHOS; i++){
    words[i]=NULL;
  }
}


void init(char s[], char d[]){
  int i;
  for(i=0;i<LINESIZE;i++){
    s[i]='\0';
    d[i]='\0';
  }
}
 
 
void make(char *sentence, char * delimiter){
  int delimLength,length;
  char * arxh;
  char * telos;
  char * word;
  int i;
  
 
  if (*delimiter !='\0' && (delimLength = strlen(delimiter)) <= LINESIZE){
    
    arxh=sentence;
    telos=strstr(arxh,delimiter);
    i=0;
    while (telos != NULL){
      length=telos-arxh;
      word=(char *) malloc((length+1)*sizeof(char));
      
      if (word==NULL){
	printf("Problem in allocation :P");
	//clear
	
      }
	
      strncpy(word,arxh,length);
      word[length+1]='\0';
      words[i]=(infoT *) malloc(sizeof(infoT));
      words[i]->d=word;
      words[i]->len=strlen(word);
      i++;
      arxh=telos+delimLength;
      telos=strstr(arxh,delimiter);
    }
  }
}
   
void print(infoT * words[]){
  int i;
  for(i=0;i<= MEGETHOS;i++){
    printf("%s , %d \n",words[i]->d,words[i]->len);
  }
}

    
 
//prepei na kanw kai thn clear gia na kanw free alla variemai twra!





int main (int argc, char * argv[]){
  char sentence[LINESIZE];
  char delimiter[LINESIZE];
  char * p;
  
  
  init_1();
  init (sentence,delimiter);
  printf("Enter sentence : \n");
  scanf("%s",sentence);
  p=(char *) malloc ((LINESIZE) * sizeof(char));
  
  printf("Enter delimiter:  \n");
  scanf("%s",delimiter);
  
  make(sentence,delimiter);
  print(words);
  return 0 ;
}