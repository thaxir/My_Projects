#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINESIZE 100
#define LINES 10
#define END "." 

typedef struct node {
	char *pword;
	int length;
	struct node *next;
} infoT;

infoT* makeList (char *sentence, char *delim);
void clearList (infoT *head);
void printList (infoT *head);

int main(int argc, char *argv[]) {

	char sentence[LINESIZE], delimiter[LINESIZE], format[15];
	int numLines, i;
	infoT *sentences[LINES];

	for (i=0; i<LINES; i++) {
		sentences[i] = NULL;
	}

	sprintf(format, "%%%ds", LINESIZE-1);

	printf("Enter delimiter: ");
	scanf(format, delimiter);
	numLines = 0;
	do {
		printf("Enter sentence: ");
		scanf(format, sentence);
		if (strcmp(sentence, END)==0) {
			break;
		}
		sentences[numLines] = makeList(sentence, delimiter);
		printList(sentences[numLines]);
		numLines++;
	} while (numLines < LINES);

	for (i=0; i<numLines; i++) {
		clearList(sentences[i]);
	}
	return 0;
}


infoT* makeList (char *sentence, char *delim) {

	char *start, *end, *word;
	int length, delimLength;
	infoT *head, *newnode, *tail;
	
	head = tail = NULL;
	delimLength = strlen(delim);

	start = sentence;
	end = strstr(start, delim);

	while (end != NULL) {

		length = end - start;
		word = (char *) malloc ((length+1)*sizeof(char));
		if (word == NULL) {
			printf("Error in memory allocation\n");
			clearList(head);
			return NULL; 
		}
		strncpy(word, start, length);
		word[length]='\0';

		newnode = (infoT*)malloc(sizeof(infoT));
		if (newnode == NULL) {
			printf("Error in node allocation\n");
			clearList(head);
			return NULL;
		}
		newnode->pword = word;
		newnode->length = length;
		newnode->next = NULL;
		if (head == NULL) {
			head = tail = newnode;
		}
		else {
			tail->next = newnode;
			tail = newnode;
		}
			
		start = end+delimLength;
		end = strstr(start, delim);
	}

	/* dokimaste na grapsete to programma wste i eisagwgi 
	tou kombou na ginetai se sunartisi, gia na apofugoume
	to copy+paste tou parakatw kwdika kai na einai pio 
	anagnwsimo to programma mas.
	*/

	word = (char *) malloc ((length+1)*sizeof(char));
	if (word == NULL) {
		printf("Error in memory allocation\n");
		return NULL; // diorthwse to
	}
	strcpy(word, start);
	length = strlen(word);
	newnode = (infoT*)malloc(sizeof(infoT));
	if (newnode == NULL) {
		printf("Error in node allocation\n");
		clearList(head);
		return NULL;
	}
	newnode->pword = word;
	newnode->length = length;
	newnode->next = NULL;
	if (head == NULL) {
		head = tail = newnode;
	}
	else {
		tail->next = newnode;
		tail = newnode;
	}

	
	return head;
}

void clearList (infoT *head) {
	infoT *runner;
	runner = head;
	while (runner != NULL) {
		head = head->next;
		free(runner->pword);
		free(runner);
		runner = head;
	}
}
void printList (infoT *head) {
	infoT *runner;
	runner = head;
	while (runner != NULL) {
		printf("%s, %d\n", runner->pword, runner->length);
		runner = runner->next;
	}
	printf("\n");
}

