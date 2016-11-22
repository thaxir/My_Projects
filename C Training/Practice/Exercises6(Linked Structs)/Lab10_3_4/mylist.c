#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"mylist.h"

nodeT *makeOneList(int howmany) {
	nodeT *newnode, *head;
	int i;
	head = (nodeT*)malloc(sizeof(nodeT));
	head->data = -1;
	head->next = head;
	head->prev = head;
	for (i=0; i<howmany; i++) {
		newnode = (nodeT*)malloc(sizeof(nodeT));
		if (newnode == NULL) {
			printf("Memory allocation error in creation of list 1\n");
			return NULL;
		}
		newnode->data = rand()%20+1;
		newnode->next = head;
		newnode->prev = head->prev;
		head->prev->next = newnode;
		head->prev = newnode;
	}
	return head;
}
			
	
int createList(nodeT **list, int size) {
	/* srand(size); // use this for debugging */
	srand((int)time(NULL));
	*list = makeOneList(size);
	return (*list != NULL);
}

/* prints the list forward and backward to verify correctness of prev pointers */
void printList(nodeT *list) {
	nodeT *current = list->next;
	
	printf("\nFORWARD: ( ");
	while (current != list) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf(")\n");
	current = list->prev;
	printf("\nBACKWARD: ( ");
	while (current != list) {
		printf("%d ", current->data);
		current = current->prev;
	}
	printf(")\n\n");
}

void emptyList(nodeT *list) {
	nodeT *current = list;
	list->prev->next = NULL;
	while (current != NULL) {
		current = list->next;
		free(list);
		list = current;
	}
}
