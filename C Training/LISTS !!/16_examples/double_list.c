/* Manipulate a list in which nodes contain a name and an AEM. Each node *
 * participates in two circular, doubly linked lists with sentinel, one  *
 * sorted by name and the other by AEM. No two nodes are allowed to have *
 * exactly the same content (name AND AEM). All allocated memory is de-  *
 * allocated before program exit										 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFF	36

struct student {
	char *name;
	int aem;
	struct student *nxt_name;
	struct student *prev_name;
	struct student *nxt_aem;
	struct student *prev_aem;
};
typedef struct student studentT;

enum type {NAME, AEM, BOTH};


/* Initializes a new list. Returns a pointer to the sentinel allocated *
 * allocated for the new list 										   */
studentT *init_list() {
	studentT *sentinel;

	sentinel = (studentT *)malloc(sizeof(studentT));
	sentinel->nxt_name = sentinel;
	sentinel->prev_name = sentinel;
	sentinel->nxt_aem = sentinel;
	sentinel->prev_aem = sentinel;

	return(sentinel);
}


/* Returns a pointer to the node containing the data we are looking for. If such *
 * a node does not exist, it returns a pointer to the node that would be next in *
 * the sentinel. We can search by name, aem, or bothdepending on the value of    *
 * which. If we search for both, either the node is returned or NULL			 */

studentT *search_node(studentT *head, enum type which, char *name, int aem) {
	studentT *curr;

	if (which == NAME) {
		head->name = name;
		for (curr = head->nxt_name; strcmp(curr->name, name) < 0; curr = curr->nxt_name);
	}
	else if (which == AEM) {
		head->aem = aem;
		for (curr = head->nxt_aem; curr->aem < aem; curr = curr->nxt_aem);
	}
	else {
		head->aem = aem;
		head->name = name;
		/* Look for a node with the same aem */
		for (curr = head->nxt_aem; curr->aem < aem; curr = curr->nxt_aem);
		/* Now, starting from that node, try to find a node with the same name as well */
		for (; curr->aem == aem && strcmp(curr->name, name) != 0; curr = curr->nxt_aem);
		/* If a node with the specific aem and name was not found, return NULL */
		if (curr == head || curr->aem != aem || strcmp(curr->name, name) != 0)
			return(NULL);
	}	
	/* If everything is OK, return a pointer to the node that was found */
	return(curr);
}


/* Print the list, either sorted by name or by aem, depending on *
 * the value of "which"											 */
void print_node(studentT *head, enum type which) {
	studentT *curr;
	
	if (which == NAME) {
		printf("Printing list by NAME\n");
		for (curr = head->nxt_name; curr != head; curr = curr->nxt_name)
			printf("%s, %d\n", curr->name, curr->aem);
	}
	else {
		printf("Printing list by AEM\n");
		for (curr = head->nxt_aem; curr != head; curr = curr->nxt_aem)
			printf("%s, %d\n", curr->name, curr->aem);
	}
}


/* Add a new node in the list(s). Make sure that another node with the same  *
 * data does not already exist. Returns: 0 if everything was OK, 1 if a node *
 * with the same data already existed, -1 if memory could not be allocated   */
int add_node(studentT *head, char *name, int aem) {
	studentT *new_node, *next_name, *next_aem;
	
	if (search_node(head, BOTH, name, aem) == NULL)
		return(1); /* A node with the specific name and aem already exists */

	/* Try to find the right position for the new node in the two lists */
	next_name = search_node(head, NAME, name, 0);
	next_aem = search_node(head, AEM, NULL, aem);
	
	new_node = (studentT *)malloc(sizeof(studentT));
	if (new_node == NULL)
		return(-1); /* Problem allocating memory for the new node */
	
	new_node->aem = aem;
	new_node->name = strdup(name);
	
	new_node->nxt_aem = next_aem;
	new_node->prev_aem = next_aem->prev_aem;
	new_node->nxt_name = next_name;
	new_node->prev_name = next_name->prev_name;
	
	new_node->prev_aem->nxt_aem = new_node;
	new_node->nxt_aem->prev_aem = new_node;
	new_node->prev_name->nxt_name = new_node;
	new_node->nxt_name->prev_name = new_node;
	
	return(0);
}


/* Reads data from the keyboard (until "end" is read) and adds the *
 * corresponding nodes to the list. In case of error appropriate   *
 * messages are printed-out and if memory can not be allocated     *
 * the program is terminated 									   */
void add_data(studentT *head) {
	char buffer[MAX_BUFF], format[10];
	int aem, retval;
	
	sprintf(format, "%%%ds", MAX_BUFF-1);
	
	printf("Adding data. Enter names and aems. Data input is terminated if \"end\" is given instead of a name\n");	
	scanf(format, buffer);
	
	while (strcmp(buffer, "end") != 0) {
		scanf("%d", &aem);
		retval = add_node(head, buffer, aem);
		if (retval == 1)
			printf("A node with the specific data already exists\n");
		else if (retval == -1) {
			printf("Memory allocation error in node addition\n");
			exit(1);
		}
		scanf(format, buffer);
	}
}


/* Remove node with the specific data (name and aem) from the list *
 * pointed-to by head. If such a node is found and removed, return *
 * 0. Return 1 otherwise 										   */
int remove_node(studentT *head, char *name, int aem) {
	studentT *node;
	
	node = search_node(head, BOTH, name, aem);
	if (node == NULL)
		return(1);
	
	node->prev_name->nxt_name = node->nxt_name;
	node->nxt_name->prev_name = node->prev_name;
	node->prev_aem->nxt_aem = node->nxt_aem;
	node->nxt_aem->prev_aem = node->prev_aem;
	
	free(node->name);
	free(node);
	
	return(0);
}

/* Removes nodes with the specific aem and name, until "end" is given as name */
void remove_nodes(studentT *head) {
	char buffer[MAX_BUFF], format[10];
	int aem, retval;
	
	printf("Removing nodes\n");
	printf("Enter name and then aem. \"end\" to finish\n");
	
	sprintf(format, "%%%ds", MAX_BUFF-1);

	scanf(format, buffer);
	while(strcmp(buffer, "end") != 0)  {
		scanf("%d", &aem);
		retval = remove_node(head, buffer, aem);
		if (retval != 0)
			printf("No node with the specific name and aem found: %s, %d\n", buffer, aem);
		
		scanf(format, buffer);
	}
}

/* Scans the list and destroys all nodes */
void destroy_list(studentT *head) {
	studentT *curr;

	printf("Destroying list\n");
	/* Why curr = curr->nxt_name is not in the for ? */
	/* Be carefull! A node can not be touched (read/written) *
	 * after it has been freed! 							 */
	/* Also, make sure that you remove the memory dynamically *
	 * allocated for the name as well!						  */
	for (curr = head->nxt_name; curr != head; ) {
		curr = curr->nxt_name;
		free(curr->prev_name->name);
		free(curr->prev_name);
	}
	free(head); /* Do not forget to deallocate the sentinel */
}


int main(int argc, char *argv[]) {
	studentT *head;

	printf("Initializing list\n");
	head = init_list();
	if (head == NULL) {
		printf("Memory allocation error for sentinel\n");
		return(1);
	}
	
	add_data(head);
	print_node(head, NAME);
	print_node(head, AEM);
	
	remove_nodes(head);
	print_node(head, NAME);
	
	destroy_list(head);
	return(0);
}
