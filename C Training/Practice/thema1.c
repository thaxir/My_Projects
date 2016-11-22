#include <stdio.h>
#include <stdlib.h>

struct list1{
  char v;
  struct list *next;
  struct list *prev;
};
 typedef struct list1 lisT;
  
  lisT*initialize(){
    lisT*sentinel;
    sentinel=(lisT*)malloc(sizeof(lisT));
    sentinel->next=sentinel;
    sentinel->prev=sentinel;
    return sentinel;
  }
  
lisT *make_list(char *str,lisT *head){
  int n;
  lisT *new,*first;
  
  first=head;
  n=sizeof(str);
  while(*str!='\0'){
    new=(char*)malloc(sizeof(char));
    new->next=first->next;
    new->prev=first;
    new->prev->next=new;
    first=new;
    str=str+1;
  }
    return head;
}
void print_list(lisT*head){
  
  lisT *runner;
  for(runner=head->next;runner!head;runner=runner->next){
    printf("%s",runner->v);
  }
}
  
  
  
  int main(int argc,char *argv[]){
    lisT *head;
    int arith;
    char buff[10];
    
    head=initialize();
    printf("dwse arithmo pou thes na valeis\n");
    scanf("%d",&arith);
    itoa(arith,buff,10);
    head=make_list(buff,head);
    print_list(head);
    
    return 0;
  }