/* Christopher Feener
 * Mastermind program
 * Started on 3 February 2019
 * This program is the codemaker currently.
 */

#include <stdio.h>
#include <stdlib.h>	//For malloc() and free()
#include <time.h>	//For time()
#include <stdbool.h>

#define BUF_SIZE 512

typedef struct board {	//Top of Hierarchy
	int num_rows;	//Maximum number of guesses
	int row_size;	//Size of code_ and key_peg arrays.
	struct row ** row_array;	//TODO: Array of pointers
	int * answer;
} Board;

typedef struct row {
	int row_size;	//Size of code_ and key_pegs arrays.
	int * code_pegs;	//Assigned to C colors
	int * key_pegs;	//Either empty, white, or red
} Row;

void setAnswer(Board * b) {
	int i, n = b->row_size;
	b->answer = (int *)calloc(n, sizeof(int));
	srand(time(0));
	for (i = 0; i < n; i++)
		b->answer[i] = rand() % 4;
}

Row * createRow(int row_size) {
	Row * r = (Row *)malloc(sizeof(Row));
	r->code_pegs = (int *)calloc(row_size, sizeof(int));
	r->key_pegs = (int *)calloc(row_size, sizeof(int));
	int i; 
	for (i = 0; i < row_size; i++)
		r->code_pegs[i] = 0;
	for (i = 0; i < row_size; i++)
		r->key_pegs[i] = 0;
	return r;
}

void freeRow(Row * r) {
	free(r->code_pegs);
	free(r->key_pegs);
	free(r);
}

Board * createBoard(int num_rows, int row_size) {
	Board * b = (Board *)malloc(sizeof(Board));
	int i;
	b->row_array = (Row **)calloc(num_rows, sizeof(Row *));
	for (i = 0; i < num_rows; i++)
		b->row_array[i] = createRow(row_size);
	b->num_rows = num_rows;
	b->row_size = row_size;
	setAnswer(b);	//Random generated
	return b;
}

void freeBird(Board * b) {
	int i, n = b->num_rows;
	for (i = 0; i < n; i++)
		freeRow(b->row_array[i]);
	free(b->row_array);
	free(b->answer);
	free(b);
}

int input(char * str, int deflt) {
	int val = deflt;	//Set initially to default.
	char buffer[BUF_SIZE] = {'\0'};
	printf("%s", str);
	if (fgets(buffer, BUF_SIZE, stdin) != NULL) {
		if (sscanf(buffer, "%i", &val) == 1)
			printf("\nValue set.\n");
	}
	return val;
}

void printAns(Board * b) {
	int i, n = b->row_size; 
	for (i = 0; i < n; i++)
		printf("%i ", b->answer[i]);
	printf("\n");
}

void printBoard(Board * b) {
	int i, j, y = b->num_rows, x = b->row_size;
	for (i = 0; i < y; i++) {
		for (j = 0; j < x; j++)
			printf("%i ", b->row_array[i]->code_pegs[j]);
		printf(" ...  ");
		for (j = 0; j < x; j++)
			printf("%i ", b->row_array[i]->key_pegs[j]);
		printf("\n");
	}
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

	printBoard(B);

	printAns(B);

	freeBird(B);
	return 0;
}
