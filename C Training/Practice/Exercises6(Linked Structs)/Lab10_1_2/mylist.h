#ifndef _MYLIST_H
#define _MYLIST_H

typedef struct node {
	int data;
	struct node *next;
} nodeT;

int createLists(nodeT **, nodeT **, int) ;
void printList(nodeT *) ;
void emptyList(nodeT *);

#endif
