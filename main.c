//TODO: Row_size and num_rows are likely swapped.

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
#define EMPTY 0
#define WHITE 1
#define RED 2

typedef struct board {	//Top of Hierarchy
	int num_rows;	//Maximum number of guesses
	int row_size;	//Size of code_ and key_peg arrays.
	struct row ** row_array;	//Array of pointers
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
		//b->answer[i] = rand() % n;
		b->answer[i] = 1;
}

Row * createRow(int row_size) {
	Row * r = (Row *)malloc(sizeof(Row));
	r->code_pegs = (int *)calloc(row_size, sizeof(int));
	r->key_pegs = (int *)calloc(row_size, sizeof(int));
	int i; 
	for (i = 0; i < row_size; i++) {
		r->code_pegs[i] = 0;
		r->key_pegs[i] = 0;
	}
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
	b->row_array = (Row **)calloc(num_rows, sizeof(Row *));	//Array space
	for (i = 0; i < num_rows; i++)
		b->row_array[i] = createRow(row_size);
	b->num_rows = num_rows;
	b->row_size = row_size;
	setAnswer(b);	//Randomly generated
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
		printf("\t\t");
		for (j = 0; j < x; j++)
			printf("%i ", b->row_array[i]->key_pegs[j]);
		printf("\n");
	}
}

bool checkGuess(Board * b, int * a, int curr_guess) {	//TODO: Wrong behavior
	bool is_match = true;
	int i, white = 0, red = 0, n = b->row_size;
	Row * r = b->row_array[curr_guess];
	int * ans = b->answer;
	for (i = 0; i < n; i++) {
		if (ans[i] != a[i])
			is_match = false;
		else red++;	//Correct position
	}
	if (!is_match) {	//Place into row
		for (i = 0; i < n; i++) {
			r->code_pegs[i] = a[i];
			int j; 
			for (j = 0; j < n; j++) {
				if (i == j) continue;
				if (a[i] == ans[j])
					white++;
			}
		}
	}
	white -= red;	//Correct letters minus position.
	for (i = 0; i < n; i++) {
		if (red > 0) {
			r->key_pegs[i] = RED;
			red--;
		} else if (white > 0) {
			r->key_pegs[i] = WHITE;
		}
	}
	return is_match;
}

int main(void) {
	int num_colors = 6;
	int num_row = 8;
	int row_size = 4;

	printf("Welcome to MasterMind->CodeMaker!\n");
	num_colors = input("Colors (default is 8): ", num_colors);
	num_row = input("Number of guesses (default is 8): ", num_row);
	row_size = input("Length of code (default is 4): ", row_size);
	printf("Colors: %i, Guesses: %i, Length: %i\n", num_colors, num_row, row_size);

	Board * B = createBoard(num_row, row_size);

	char buffer[BUF_SIZE] = {'\0'};
	bool is_found = false;
	int i = 0;
	while (i < row_size) {
		printf("Current board: \n");
		printBoard(B);
		if (fgets(buffer, BUF_SIZE, stdin) == NULL) {
			printf("Please enter a guess\n");
			continue;
		}
		int a[4] = {0, 0, 0, 0};
		if (sscanf(buffer, "%i %i %i %i", &a[0], &a[1], &a[2], &a[3]) != row_size) {
			printf("Please enter 4 numbers\n");
			continue;
		}
		if ((is_found = checkGuess(B, a, i)) == true) {
			printf("Congratulations! You found the answer!\n");	//Check guess
			break;
		}
		i++;
	}

	if (!is_found) {
		printf("You lost. Answer: ");
		printAns(B);
	}

	freeBird(B);
	return 0;
}
