/* Christos Antonopoulos, Computer and Communication Engineering Department, *
 * University of Thessaly, Greece											 *
 * http://www.inf.uth.gr/~cda												 */

/* The program reads a sudoku board from the command line. The format is :	 *
 * SIZE lines of SIZE elements each, terminating with a new line character.  *
 * Empty rectangles correspond to dots '.', given initial values to 		 *
 * arithmetic digits. The program prints-out the solution, or a message that *
 * no solution was found.													 */
#include <stdio.h>

#define SIZE		9	/* Dimension of the sudoku rectangle board */
#define SUB_SIZE	3	/* Dimension of each sub-rectangle within the sudoku board */


/* Initialize the table */
void init(int board[][SIZE]) {
	int i, j;
  
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			board[i][j] = 0;
}


/* Read the input puzzle fron the command-line and put known values in the board */
void read_input(int board[][SIZE]) {
	int i, j;
	char in[SIZE+1], format[10];
	
	sprintf(format, "%%%ds", SIZE);
  
	for (i = 0; i < SIZE; i++) {
		scanf(format, in);				/* Read initial puzzle from input line-by-line */
		for (j = 0; j < SIZE; j++) 		/* For each line */
			if (in[j] != '.')					/* If the corresponding character *
											 	 	 * read is '.', leave the 0 on the*
											 	 	 * board as is...				  */
				board[i][j] = in[j] - '0';	/* Otherwise replace the value on *
											 		 * the board with the numerical   *
											 		 * value corresonding to the 	  	 *
											 		 * character read. 				  	 */
	}
}


/* Print-out the table */
void print_table(int board[][SIZE]) {
	int i, j;
  
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) 
			printf("%d", board[i][j]);
		printf("\n");
	}
}


/* Check that there are no numbers within a row "row" *
 * equal to the number "num" positioned in (row, col).*
 * If there is a duplicate, return 0, otherwise return*
 * 1												  */
int check_row(int row, int col, int num, int board[][SIZE]) {
	int j;
  
	for (j = 0; j < col; j++)
		if (board[row][j] == num)
			return(0);
	for (j = col+1; j < SIZE; j++)
		if (board[row][j] == num)
			return(0);
      
  return(1);
}


/* Check that there are no numbers within a column "col" *
 * equal to the number "num" positioned in (row, col).   *
 * If there is a duplicate, return 0, otherwise return   *
 * 1												     */
int check_col(int row, int col, int num, int board[][SIZE]) {
	int i;
  
	for (i = 0; i < row; i++)
		if (board[i][col] == num)
			return(0);
	for (i = row+1; i < SIZE; i++)
		if (board[i][col] == num)
			return(0);
		
	return(1);
}

/* Check that there are no numbers equal to the number "num" positioned *
 * in (row, col), within the SUB_SIZE x SUB_SIZE sub-rectangle that		* 
 * contains (row, col) If there is a duplicate, return 0, otherwise 	*
 * return 1												     			*/
int check_subrect(int row, int col, int num, int board[][SIZE]) {
	int sub_row, sub_col; /* Starting row / column of the sub-rectangle */
	int i, j;
  
	sub_row = (row / SUB_SIZE) * SUB_SIZE;	/* This is the row where the sub-rectangle begins */
	sub_col = (col / SUB_SIZE) * SUB_SIZE;	/* This is the column where the sub-rectangle begins */
  
	for (i = sub_row; i < sub_row + SUB_SIZE; i++)
		for (j = sub_col; j < sub_col + SUB_SIZE; j++)
			if (board[i][j] == num && (i != row || j != col))
				return(0);
    
	return(1);
}


/* Find the next rectangle on the board (new_row, new_col), provided *
 * that you are on (row, col). You may have to change row! If you 	 *
 * were on the last rectangle of the board, congrats, we have found  *
 * a solution. Return 1! Otherwise, return 0 and - of course - the   *
 * coordinates of the next rectangle 								 */
int find_next_rect(int *new_row, int *new_col, int row, int col) {
	*new_col = (col + 1) % SIZE;
	if (*new_col == 0) {
		*new_row = row + 1;
		if (*new_row == SIZE)
			return(1); /* We have a solution */
	}
	else
		*new_row = row;
	return(0);
}

/* Solves the puzzle. Returns 1 if a solution is found, 0 otherwise */
int solve(int row, int col, int board[][SIZE]) {
	int new_row, new_col, num;
  
	if (board[row][col] != 0) {	 									 /* This is a fixed number in the puzzle... */
		if (find_next_rect(&new_row, &new_col, row, col) == 1) /* ... so move to the next rectangle    */
			return(1);										   			 /* If the next rectangle is after the   */
															   				 /* end of the board, we have a solution */
		return(solve(new_row, new_col, board)); 	/* Otherwise, repeat solve for the next rectangle. This*
												 				 * will be the common case.									 */
	}
	else {													/* Normal case. We are on an "empty" rectangle */
		for (num = 1; num <=9; num++) {				/* Try all possible numbers for this rectangle */
			if (check_row(row, col, num, board) && /* If there is no conflict on rows, columns and*/
				check_col(row, col, num, board) &&  /* subrectangles... 						   */
				check_subrect(row, col, num, board)) {
				board[row][col] = num;												/* Set this value on the board ... */
				if (find_next_rect(&new_row, &new_col, row, col) == 1) 	/* ... and move to the next rectangle */
					return(1);										   				/* If the next rectangle is after the */
																	   					/* end of the board, we have a solution */
				if (solve(new_row, new_col, board) == 1) /* Otherwise, repeat solve for the next rectangle. This*
														  				* will be the common case.							*/
					return(1);			 /* If solve returns one, we have a solution! */
				else {					 /* Since we arrived here, it means that no solution can be found with *
											  * the current setup of numbers already positioned on the board, so...*/
					board[row][col] = 0; /* ... we 'll undo the last change (num on (row, col)) */
				}
			}  /* And we 'll move to the next loop iteration, trying the next num on the specific rectangle */
		}
		
		return(0);    
	}
}


int main(int argc, char *argv[]) {

	int table[SIZE][SIZE];	/* This is the sudoku board */
  
	init(table);  
	read_input(table);
	if (solve(0, 0, table)) {
		printf("SOLUTION\n");
		print_table(table);  
	}
	else 
		printf("NO SOLUTION\n");
   
	return(0);
}
