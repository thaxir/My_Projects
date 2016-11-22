#include<stdio.h>
#include<stdlib.h>
#include"mylist.h"

void augmentList(nodeT* list, int step, int data);

int main (int argc, char *argv[]) {
	nodeT *list;
	int ok, numelements, step;
	printf("How many elements in a list? ");
	scanf("%d", &numelements);
	ok = createList(&list, numelements);
	if (!ok) {
		printf("Error creating list\n");
		return 1;
	}

	printf("Before: ");
	printList(list);

	do {
		printf("Enter step (>=2) : ");
		scanf("%d", &step);
	} while (step < 2);

	augmentList(list, step, 0);

	printf("After: ");
	printList(list);

	emptyList(list);
	return 0;
}

void augmentList(nodeT *list, int step, int data) {
  int i;
  nodeT*runner;
  nodeT*nea_arxh;
  nodeT*new;
  
  
  runner=list->next;
  nea_arxh=list->next;
  
  do{
    for(i=1;i<step;i++){
      runner=runner->next;
    }
    if(runner==list){
      break;
    }
      new=(nodeT*)malloc(sizeof(nodeT));
      new->data=data;
      new->next=runner->next;
      new->prev=runner;
      new->prev->next=new;
      new->next->prev=new;
    
      nea_arxh=new->next;
  
  
  }while(nea_arxh!=list);
 
  
}
		
