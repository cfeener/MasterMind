/* Christopher Feener
 * Mastermind program
 * Started on 3 February 2019
 * This program will output randomly according to rules at first.
 */

#include <stdio.h>

typedef struct board {	//Top Hierarchy
	int chances;	//Maximum number of guesses
	int row_size;
	Row * row;
	Row * answer;
} Board;

typedef struct row {
	int * code_pegs;	//Assigned to C colors
	int row_size;	//Size of code_ and key_pegs arrays.
	int * key_pegs;	//Either empty, white, or red
} Row;

int main(void) {
	return 0;
}
