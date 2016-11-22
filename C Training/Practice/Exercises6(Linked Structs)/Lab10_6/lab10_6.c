#include<stdio.h>
#include<stdlib.h>
#include"mylist.h"

nodeT*  duplicateList(nodeT* list);

int main (int argc, char *argv[]) {
	nodeT *list;
	int ok, numelements;
	printf("How many elements in a list? ");
	scanf("%d", &numelements);
	ok = createList(&list, numelements);
	if (!ok) {
		printf("Error creating list\n");
		return 1;
	}

	printf("Before: ");
	printList(list);

	  list=duplicateList(list);						/* kaleste edw ti sunartisi duplicateList */

	printf("After: ");
	printList(list);

	emptyList(list);
	return 0;
}

nodeT * duplicateList(nodeT *list) {
  nodeT*runner;
  nodeT*new;					//nomizw exw valei polous deiktes :)  pout*** ola
  nodeT*root;
  nodeT*curr;
  
  new=(nodeT*)malloc(sizeof(nodeT));
  new->data=list->data;
  new->next=list;
  new->prev=list->prev;
  new->next->prev=new;
  new->prev->next=new;
  
  root=new;
  for(runner=list->next;runner!=root;runner=runner->next){
    curr=(nodeT*)malloc(sizeof(nodeT));
    curr->data=runner->data;
    curr->next=runner;
    curr->prev=runner->prev;
    curr->prev->next=curr;
    curr->next->prev=curr;
  }
    	return (root);
}
