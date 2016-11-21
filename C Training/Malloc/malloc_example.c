#include <stdio.h>
#include <stdlib.h>

int *read_names(int num_students) {
  int *aem_array_ptr;
  int i;

  aem_array_ptr = (int *)malloc(sizeof(int) * num_students);
  if (aem_array_ptr == NULL) {
    printf("Memory allocation problem\n");
    return(NULL);
  }

  for (i = 0; i < num_students; i++) {
    scanf("%d", aem_array_ptr + i);
/*    scanf("%d", &aem_array_ptr[i]);*/
  }

  return(aem_array_ptr);
}

int main(int argc, char *argv[]) {
  int howmany, i;
  int *table;

  printf("How many students? ");
  scanf("%d", &howmany);

  table = read_names(howmany);
  if (table == NULL) {
    printf("In main: Memory allocation problem. Exiting\n");
    return(1);
  }
  
  for (i = 0; i < howmany; i++) {
      printf("%d\n", *(table + i));
/*    printf("%d\n", table[i]);*/
  }

  free(table);
  table = NULL;

  return(0);
}
