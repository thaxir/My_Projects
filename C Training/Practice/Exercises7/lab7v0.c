#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20
#define SIZE 3


typedef struct {
  char title[N];
  char author[N];
  int availability;
}infoT;


int find_book(infoT books[]){
  char tit[N],aut[N];
  int i;
  
  printf("enter title and author you wanna find \n");
  scanf("%s %s",tit,aut);
  
  for(i=0;i<SIZE;i++){
    if(strcmp(books[i].title,tit)==0 && strcmp(books[i].author,aut)==0){
      return (books[i].availability);
    }
  }
  return 0;
}
  
void print(infoT books[],int c){
  int i;
  for(i=0;i<c;i++){
    printf("%s %s %d\n",books[i].title,books[i].author,books[i].availability);
  }
}

int main(int argc,char *argv[]){
  int num,i,p;
  infoT books[SIZE];
  
  do{
    printf("Enter number of books \n");
    scanf("%d",&num);
  }while(num>SIZE  || num<0);
  
  for(i=0;i<num;i++){
    printf("enter title \n");
    scanf("%s",books[i].title);
    printf("enter owner \n");
    scanf("%s",books[i].author);
    books[i].availability=1;
  }
  
  p=find_book(books);
  if(p==1){
    printf("book found\n");
  }
  else{
      printf("book not found \n");
  }
  print(books,num);
    return 0;
  }