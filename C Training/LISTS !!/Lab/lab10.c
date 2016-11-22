#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NAMESIZE 50
#define END "." 

/* ~~~~~~   TYPES   ~~~~~~ */

typedef struct node {
	char *name;
	int age;
	struct node *next;
	struct node *prev;
} infoT;

/* ~~~~~~   PROTOTYPES   ~~~~~~ */

infoT * initialize(int); /* arxikopoiei ti lista kai ti gemizei stoixeia. 
						De xreiazetai na gnwrizete pws ginetai auto */
infoT* insert(infoT *head, char *name, int age, int steps);
void clearList(infoT *head);
void printList(infoT *head);

/* ~~~~~~   MAIN   ~~~~~~ */

int main(int argc, char *argv[]) {
	char name[NAMESIZE], format[15];
	int age, step, numElements;
	infoT *head; /* i kefali tis listas */
	do {
		printf("Enter initial number of elements (>=1): ");
		scanf("%d", &numElements);
	} while (numElements < 1);

	head = initialize(numElements);
	printf("The following list has been created: ");
	printList(head);

	sprintf(format, "%%%ds", NAMESIZE-1);

	while(1) {
		printf("\nEnter name or . to finish: ");
		scanf(format, name);
		if (strcmp(name, END)==0) {
			break;
		}
		printf("Enter age: ");
		scanf("%d", &age);	
		do {
			printf("Enter step (>0): ");
			scanf("%d", &step);
		} while (step <= 0);
		head = insert(head, name, age, step);
		printList(head);
	};
	clearList(head);
	return 0;
}

/* 
Pairnei ws parametrous tin kefali tis listas, onoma, ilikia kai arithmo
bimatwn. Prosthetei sti lista tosous neous kombous (me to sugkekrimeno
onoma kai ilikia) osoi xreiazontai wste na uparxei enas neos kombos
kathe toses "theseis" osos einai o arithmos bimatwn. 
Epistrefei tin kefali tis listas.
I lista einai dipla diasundedemeni, mi-kukliki, xwris termatiko.
*/
infoT* insert(infoT *head, char *name, int age, int steps) {
  infoT * curr;
  infoT * runner;
  infoT * previous;
  int i;
  
  runner=head;
  while(runner!=NULL){
    
  for(i=0; i!=steps && runner!=NULL;i++){
    previous=runner;
    runner=runner->next;
  }
  if (runner==NULL){
    break;
  }
  curr=(infoT*)malloc(sizeof(infoT));
  if (curr=NULL){
    printf("cannot allocate : \n");
    free(curr);
    return head;
  }
    
  curr->age=age;
  curr->name=(char *)malloc((strlen(name)+1)*sizeof(char));
  strcpy(curr->name,name);
  
  curr->next=runner;
  curr->prev=previous;
  curr->next->prev=curr;
  curr->prev->next=curr;
  
  
  }
  return head;
}

/* 
clearList
Pairnei ws parametro tin kefali tis listas kai apeleutherwnei 
oli ti dunamika desmeumeni mnimi gi'auti */

	
void clearList(infoT *head) {
  infoT * runner;
  
	runner=head;
	
	while(runner!=NULL){
	  runner=head->next;
	  free(head->name);
	  free(head);
	  head=runner;
	}
}	
	
/* 
printList
Pairnei ws parametro tin kefali tis listas ki ektupwnei ta
periexomena tis */

void printList(infoT *head) {
	infoT *runner = head;
	int dataPerLine=0;
	printf("\n[\n");
	while (runner != NULL) {
		printf("(%s, %d)\t", runner->name, runner->age);
		runner = runner->next;
		if (++dataPerLine % 4 == 0) {
			printf("\n");
		}
	}
	printf("\n]\n");
}
