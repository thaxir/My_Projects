/* Create and manipulate a hash table for storing words. The hash table has   *
 * HASH_SIZE buckets, each being the head of a singly-linked non-circular list*
 * with sentinel. The nodes within a list are not sorted.                     */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 13
#define MAX_WORD_LEN 257
#define FORMAT_BUFF_LEN 6


/* This is the struct describing of a list node */
struct list {
  char *word;
  struct list *nxt;
};

/* The global hash table */
struct list *hash_table[HASH_SIZE];


/* Hash table initialization. After this step all lists, each starting from a *
 * cell of the table are initialized                                          */                           
void init_hash_table(void) {
  int i;
  
  for (i=0; i<HASH_SIZE; i++) {
    /* Allocate the sentinel */
    hash_table[i] = (struct list *)malloc(sizeof(struct list));
    /* Make the next pointer of the sentinel NULL to designate an empty list */
    hash_table[i]->nxt = NULL;
  }
}


/* Prints the words in the nodes of a list pointed to by head, seperated by   *
 * white spaces                                                               */
void print_list(struct list *head){
  struct list *curr;
  
  curr = head->nxt;
  while (curr != NULL) {
    printf("%s ", curr->word);
    curr = curr->nxt;
  }
  printf("\n");
}


/* Adds a new node, containing word as its data, to the beginning of the list *
 * pointed to by head                                                         */                                                                               
void list_add (struct list *head, char *word) {
  struct list *new_node;
  
  /* Allocate memory for the new node */
  new_node = (struct list *)malloc(sizeof(struct list));
  /* Allocate exactly as much memory as needed * 
   * for the string (the data in the node)     */
  new_node->word = (char *)malloc((strlen(word)+1)*sizeof(char));
  strcpy(new_node->word, word);
  
  /* Insert the new node in the list */
  new_node->nxt = head->nxt;
  head->nxt = new_node;
}


/* Looks in the list pointed to by head for a node containing word as its     *
 * data. If found, the function returns a pointer to the previous node in the *
 * list. Otherwise it returns NULL.                                           */                                                                                
struct list *list_search (struct list *head, char *word) {
  struct list *curr, *prev;
    
  curr = head->nxt;
  prev = head;
  while (curr != NULL && strcmp(curr->word, word)) {
    prev = curr;
    curr = curr->nxt;
  }
  
  if (curr != NULL)
    return(prev);
  else
    return(NULL);
}

/* Removes a node, containing word as its data, from the list pointed to by   *
 * head, if such a node exists in the specific list                           */                                                                               
void list_rmv(struct list *head, char *word) {
  struct list *prev, *curr;
  
  /* Look for the node */
  prev = list_search(head, word);
  if (prev != NULL) {
    /* Remove the node */
    curr = prev->nxt;
    prev->nxt = curr->nxt;
    /* Free the memory dynamically allocated for both the *
     * string (data) and the node itself in that order    */
    free(curr->word);
    free(curr);
  }
}


/* Hash function. Takes a word a returns the bucket (the position in the hash *
   table where the list in which the word "belongs" starts). Black magic!     */ 
int hash_function (char *word) {
  unsigned long hash = 5381;
  int c;
  
  /* Calculate the bucket based on the characters of the word. The loop goes  *
   * on until \0 is encountered (how does that happen?)                       */
  while ((c = *word++))
    hash = ((hash << 5) + hash) + c;
  
  return(hash % HASH_SIZE);
}


/* Print the contents of the hash table */
void hash_table_print(void) {
  int i;
  for (i=0; i<HASH_SIZE; i++) {
    printf("Bucket %2d: ", i);
    print_list(hash_table[i]);
  }
}


/* Look for word in the hash table. Returns 1 if the word exists, 0 otherwise */
int hash_search(char *word) {
  int hash_pos;
  struct list *prev;
  
  /* Find the correct bucket (position) */
  hash_pos = hash_function(word);
  /* Look in the list starting from that position */
  prev = list_search(hash_table[hash_pos], word);
  if (prev != NULL)
    return(1);
  return(0);
}


/* Inserts word in the hash table */
void hash_insert (char *word) {
  int hash_pos;
  
  /* Find the correct bucket (position) */
  hash_pos = hash_function(word);
  /* Perform a node insertion in the list starting from that position */
  list_add(hash_table[hash_pos], word);
}


/* Removes word from the hash table */
void hash_rmv (char *word) {
  int hash_pos;
  
  hash_pos = hash_function(word);
  list_rmv(hash_table[hash_pos], word);
}


/* Print menu, get user selection (until valid) and return it */
int menu(void) {
  int selection;

  do {
    printf("1: Enter a new word\n");
    printf("2: Search for a word\n");
    printf("3: Remove a word\n");
    printf("4: Print table\n");
    printf("0: Exit\n\n");
    printf("Your selection? ");
    scanf("%d", &selection);
    if(selection < 0 || selection >4)
      printf("Invalid selection: %d\n\n", selection);
  } while (selection < 0 || selection >4);
  return(selection);
}

int main (int argc, char *argv[]) {
  int sel;
  char format_buff[FORMAT_BUFF_LEN], input_buff[MAX_WORD_LEN];
  
  /* Initialize the hash table */
  init_hash_table();
  /* Create the format specifier string for scanf at run-time */
  sprintf(format_buff, "%%%ds", MAX_WORD_LEN-1);
  
  do {
    sel = menu();
    switch(sel) {
      case 1: printf("Enter word to add: ");
              scanf(format_buff, input_buff);
              hash_insert(input_buff);
              break;
      case 2: printf("Enter word to find: ");
              scanf(format_buff, input_buff);
              if (hash_search(input_buff))
                printf("Found\n");
              else
                printf("Not found\n");
              break;
      case 3: printf("Enter word to remove: ");
              scanf(format_buff, input_buff);
              hash_rmv(input_buff);
              break;
      case 4: printf("Current table status:\n");
              hash_table_print();
              printf("\n");                         
    }
  } while (sel != 0);
  
  return(0);
}
