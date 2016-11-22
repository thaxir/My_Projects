#include<stdio.h>
#include<stdlib.h>
#include"mylist.h"

nodeT *makeCommonList(nodeT *list1, nodeT *list2);

int main (int argc, char *argv[]) {
	nodeT *list1, *list2, *newlist;
	int ok, numelements;

	printf("How many elements in a list? ");
	scanf("%d", &numelements);
	ok = createLists(&list1, &list2, numelements);
	if (!ok) {
		printf("Error creating lists\n");
		return 1;
	}

	/* kaleste edw ti sunartisi makeCommonList */
	newlist=makeCommonList(list1,list2);

	printf("List 1: ");
	printList(list1);
	printf("List 2: ");
	printList(list2);
	printf("New List: ");
	printList(newlist);

	emptyList(list1);
	emptyList(list2);
	emptyList(newlist);
	return 0;
}

nodeT *makeCommonList(nodeT *list1, nodeT* list2) {
	nodeT*runner1;
	nodeT*runner2;
	nodeT*new;
	nodeT*curr;
	
	runner1=list1;
	new=NULL;
	
	for(runner1=list1;runner1!=NULL;runner1=runner1->next){
	  for(runner2=list2;runner2!=NULL;runner2=runner2->next){		  /*edw ama exei koina stoixeia h prwth lista tha ksanaftiaxnei komvous opws kai sthn apo katw loupa .kanonika thelei ena voit
										  ena voithitiko pinaka pou na pernei tis times kai meta kanei elegxo */
	    if(runner1->data == runner2->data){
	      curr=(nodeT*)malloc(sizeof(nodeT));
	      curr->data=runner2->data;
	      curr->next=new;
	      new=curr;
	    }    
	  }
	}
   	/*I parakatw grammi einai proswrini, gia na kanei compile to programma */
	return (new);
}

		
