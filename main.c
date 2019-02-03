/* Christopher Feener
 * Mastermind program
 * Started on 3 February 2019
 * This program is the codemaker currently.
 */

#include <stdio.h>
#include <stdlib.h>	//For malloc and free
#include <stdbool.h>

#define BUF_SIZE 512

typedef struct board {	//Top of Hierarchy
	int num_row;	//Maximum number of guesses
	int row_size;	//Size of code_ and key_peg arrays.
	struct row * row_array;
	int * answer;
} Board;

typedef struct row {
	int * code_pegs;	//Assigned to C colors
	int row_size;	//Size of code_ and key_pegs arrays.
	int * key_pegs;	//Either empty, white, or red
} Row;

void setAnswer(Board * b) {
	int i, n = b->row_size;
	b->answer = (int *)calloc(n, sizeof(int));
	for (i = 0; i < n; i++)
		b->answer[i] = rand() % 4;
}

Board * createBoard(int n_row, int r_size) {
	Board * b = (Board *)malloc(sizeof(Board));
	b->num_row = n_row;
	b->row_size = r_size;
	b->row_array = (Row *)calloc(b->num_row, sizeof(Row));
	setAnswer(b);	//Random
	return b;
}

void freeBird(Board * b) {
	free(b->row_array);
	free(b->answer);
	free(b);
}

Row * createRow(int row_size) {
	Row * r = (Row *)malloc(sizeof(Row));
	r->row_size = row_size;
	return r;
}

int input(char * str, int def) {
	int val = def;
	char buffer[BUF_SIZE] = {'\0'};
	printf("%s", str);
	if (fgets(buffer, BUF_SIZE, stdin) != NULL) {
		if (sscanf(buffer, "%i", &val) == 1)
			printf("\nValue set.\n");
	}
	return val;
}

int main(void) {
	int num_colors = 8;
	int num_row = 8;
	int row_size = 4;

	int buffer[BUF_SIZE] = {'\0'};
	printf("Welcome to MasterMind->CodeMaker!\n");
	num_colors = input("Colors (default is 8): ", num_colors);
	num_row = input("Number of guesses (default is 8): ", num_row);
	row_size = input("Length of code (default is 4): ", row_size);
	printf("Colors: %i, Guesses: %i, Length: %i\n", num_colors, num_row, row_size);

	Board * B = createBoard(num_row, row_size);
	int i; 
	for (i = 0; i < row_size; i++)
		printf("%i ", B->answer[i]);

	freeBird(B);
	return 0;
}
