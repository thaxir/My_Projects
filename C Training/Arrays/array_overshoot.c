#include <stdio.h>

/* Compile with: gcc -Wall -g -O0 array_overshoot.c -o array_overshoot */

/* The out-of-bounds array write at array[10] resets the loop counter i
 * which happens to be located in memory right after the array. This 
 * results to an infinite loop 											*/

int main (int argc, char *argv[]) {
  int array[10];
  int i;

/* Uncomment the printf to verify that &array[10] is actually &i  
 * printf("&a[10] = %p, &i = %p\n", &array[10], &i); */

for (i=0; i <= 10; i++) {
    array[i] = 0;
    printf("In loop, i = %d\n", i);
  }

  return(0);
}
