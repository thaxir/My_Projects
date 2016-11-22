#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 4
#define MEG 40

typedef enum {
  AVAILABLE =1,
  RESERVED,
  LOST
}statusT;

typedef struct {
  char writer[MEG];
  char title[MEG];
  statusT b ;
} bookinfoT;



void get_data(bookinfoT vivlia[]){
  int i;
  
  for(i=0;i<N;i++){
    printf("Dwse syggrafea titlo kai status gia to %d  vivlio: (me keno endiamesa)\n",i);
    scanf("%s %s %u",vivlia[i].writer,vivlia[i].title,&vivlia[i].b);
  }
  //for(i=0;i<N;i++){
  //  printf("vivlio %d sygrafeas %s titlos %s status %d\n",i,vivlia[i].writer,vivlia[i].title,vivlia[i].b);
  //}
}

int find_book(bookinfoT vivlia[],bookinfoT psakse){
  int i;
  for(i=0;i<N;i++){
    if((strcmp(psakse.writer,vivlia[i].writer))==0 && (strcmp(psakse.title,vivlia[i].title)==0) ){
      return 1;
      exit (0);
    }
  }
  return 0; 
}

void print_books(bookinfoT vivlia[]){
  int i;
  
  for(i=0;i<N;i++){
    printf("vivlio %d \nsygrafeas %s \ntitlos %s \nstatus %u\n\n\n",i,vivlia[i].writer,vivlia[i].title,vivlia[i].b);
  }
}
  
  
int main(int argc,char * argv[]){
  bookinfoT vivlia[N];
  bookinfoT ypops;
  int j;
  
  get_data(vivlia);
  printf("Dwse vivlio pou thes na psaksei prwta sygrafea meta titlo \n");
  scanf("%s %s",ypops.writer,ypops.title);
  j=find_book(vivlia,ypops);
  if(j==1){
    printf("FOUND\n");
  }
  else 
    printf("NOT FOUND \n");
  
  print_books(vivlia);
  
  
 
  return 0;
}