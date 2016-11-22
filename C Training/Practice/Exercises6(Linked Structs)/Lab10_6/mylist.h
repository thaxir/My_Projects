#ifndef _MYLIST_H
#define _MYLIST_H

typedef struct node {
	int data;
	struct node *next;
	struct node *prev;
} nodeT;
nodeT *makeOneList(int howmany) ;
int createList(nodeT **list, int size) ;
void printList(nodeT *list) ;
void emptyList(nodeT *list) ;
#endif
