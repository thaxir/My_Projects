#include <stdio.h>
#define ROWS 4 /* assumption: ROWS is always even */
#define COLS 3



void reverse(int table[][COLS]){
  int i,j,temp;
  
  for(i=0;i<ROWS/2;i++){
    for(j=0;j<COLS;j++){
      temp=table[i][j];
      table[i][j]=table[ROWS-i-1][COLS-j-1];
      table[ROWS-i-1][COLS-j-1]=temp;
    }
  }
} 



int main (int argc, char *argv[]) {
	int i,j, table[ROWS][COLS];

	/* read in table */
	for (i=0; i<ROWS; i++) {
		for (j=0; j<COLS; j++) {
			scanf("%d", &table[i][j]);
		}
	}

	reverse(table);
	/* print reversed table */

	for (i=0; i<ROWS; i++) {
		for (j=0; j<COLS; j++) {
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
	return 0;
}