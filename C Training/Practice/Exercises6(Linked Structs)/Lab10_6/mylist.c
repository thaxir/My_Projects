#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mylist.h"

nodeT *makeOneList(int howmany) {
	nodeT *newnode, *head, *tail;
	int i;
	head = NULL;
	for (i=0; i<howmany; i++) {
		newnode = (nodeT*)malloc(sizeof(nodeT));
		if (newnode == NULL) {
			printf("Memory allocation error in creation of list 1\n");
			return NULL;
		}
		newnode->data = rand()%20+1;
		newnode->next = NULL;
		if (head == NULL) {
			head = tail = newnode;
			head -> prev = NULL;
		}	
		else {
			tail->next = newnode;
			newnode->prev = tail;
			tail = newnode;
		}
	}
	return head;
}
			
	
int createList(nodeT **list, int size) {
	/* srand(size); // use this for debugging */
	srand((int)time(NULL));
	*list = makeOneList(size);
	return (*list != NULL);
}

void printList(nodeT *list) {
	nodeT *current = list, *prev = NULL;
	printf("\nFORWARD:( ");
	while (current != NULL) {
		printf("%d ", current->data);
		prev = current;
		current = current->next;
	}
	printf(")\n");
	current = prev;
	printf("\nBACKWARD:( ");
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->prev;
	}
	printf(")\n\n");
}

void emptyList(nodeT *list) {
	nodeT *current = list;
	while (current != NULL) {
		current = list->next;
		free(list);
		list = current;
	}
}
