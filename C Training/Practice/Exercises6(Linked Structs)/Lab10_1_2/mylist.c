#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mylist.h"

/* generates a different integer every time it is called. Range: 1 through *plimit */
int get_random_number(int *plimit, int avail_nums[]) {
	int num, index;
	index = rand()%(*plimit);
	num =  avail_nums[index];
	avail_nums[index]=avail_nums[--(*plimit)];
	return num;
}
	
nodeT *makeOneList(int howmany) {
	nodeT *newnode, *head;
	int *avail_nums, limit, i;

	limit = 2*howmany; /* increase the range of available numbers by a factor of 2 */

	avail_nums = (int *)malloc(limit*sizeof(int));
	if (avail_nums == NULL) {
		printf("Memory allocation error in list creation\n");
		return NULL;
	}
	for (i=0; i<limit; i++) {
		avail_nums[i]=i+1;
	}
		
	head = NULL;
	for (i=0; i<howmany; i++) {
		newnode = (nodeT*)malloc(sizeof(nodeT));
		if (newnode == NULL) {
			printf("Memory allocation error in list creation\n");
			return NULL;
		}
		newnode->data = get_random_number(&limit, avail_nums);
		newnode->next = head;
		head = newnode;
	}
	free(avail_nums);
	return head;
}
			
	
int createLists(nodeT **list1, nodeT **list2, int size) {
	/*srand(size); // use this for debugging */
	srand((int)time(NULL));
	*list1 = makeOneList(size);
	*list2 = makeOneList(size);
	return (*list1 != NULL && *list2 != NULL);
}

void printList(nodeT *list) {
	nodeT *current = list;
	printf("( ");
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf(")\n");
}

void emptyList(nodeT *list) {
	nodeT *current = list;
	while (current != NULL) {
		current = list->next;
		free(list);
		list = current;
	}
}
