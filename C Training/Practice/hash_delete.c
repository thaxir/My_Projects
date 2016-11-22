#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void hash_delete(char word[]) {
  int i;
  hashNode *curr,*prev;
  
  p=hash(word);
  curr=table(p);
  prev=NULL;
  while(curr!=NULL){
    if(strcmp(curr->word,word)==0){
      if(prev=NULL){
	table(p)=curr->next;
      }
      else{
	prev->next=curr->next;
      }
     free(curr);
     return;
    }
      
    prev=curr;
    curr=curr->next;
    
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
				/* prostheste tin klisi tis sunartisis edw */
				break;
			case 4: return 0;
			default: printf("Incorrect selection.");
		}
	} 
	return 0;
}
