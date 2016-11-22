#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* ARXI LYSIS*/
#include"hash_delete.h"
/* TELOS LYSIS */


void hash_delete(char word[]) {
	/* ARXI LYSIS*/
	int loc;
	hashNode *runner, *prev;

	loc = hash(word); 
	runner = table[loc];
	prev = NULL;

	while (runner != NULL) {
		if (strcmp(runner->word, word)==0) {
			if (prev == NULL) { /* remove first element of list */
				table[loc] = runner->next;
			}
			else { /* remove middle or last element */
				prev->next = runner->next;
			}
			free(runner);
			return;
		}
		prev = runner;
		runner = runner->next;
	}
	/* TELOS LYSIS */
}
	

int main () {
	int op;
	char word[27];
	initTable();
	
	while(1) {
		printf("Select operation: \n");
		printf("1. Print table\n2. Insert word\n3. Remove word\n4. Exit\n-->");
		scanf("%d", &op);
		switch(op) {
			case 1: printTable();
				break;
			case 2: printf("Enter word: ");
				fscanf(stdin, "%26s", word);
				insert(word);
				break;
			case 3: printf("Enter word: ");
				fscanf(stdin, "%26s", word);
				/* ARXI LYSIS*/
				hash_delete(word);
				/* TELOS LYSIS */
				break;
			case 4: return 0;
			default: printf("Incorrect selection.");
		}
	} 
	return 0;
}
