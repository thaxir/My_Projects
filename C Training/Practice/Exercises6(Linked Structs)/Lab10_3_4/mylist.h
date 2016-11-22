#ifndef _MYLIST_H
#define _MYLIST_H

typedef struct node {
	int data;
	struct node *next;
	struct node *prev;
} nodeT;

int createList(nodeT **, int) ;
void printList(nodeT *) ;
void emptyList(nodeT *);

#endif
