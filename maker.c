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
	int colors;
	struct row ** row_array;	//Array of pointers
	int * answer;
} Board;

typedef struct row {
	int row_size;	//Size of code_ and key_pegs arrays.
	int * code_pegs;	//Assigned to C colors
	int * key_pegs;	//Either empty, white, or red
} Row;

void setAnswer(Board * b) {
	int i, n = b->colors;
	b->answer = (int *)calloc(n, sizeof(int));
	srand(time(0));
	for (i = 0; i < n; i++)
		b->answer[i] = rand() % n + 1;
}

Row * createRow(int row_size) {
	Row * r = (Row *)malloc(sizeof(Row));
	r->code_pegs = (int *)calloc(row_size, sizeof(int));
	r->key_pegs = (int *)calloc(row_size, sizeof(int));
	int i; 
	for (i = 0; i < row_size; i++) {
		r->code_pegs[i] = -1;
		r->key_pegs[i] = 0;
	}
	return r;
}

void freeRow(Row * r) {
	free(r->code_pegs);
	free(r->key_pegs);
	free(r);
}

Board * createBoard(int num_rows, int row_size, int colors) {
	Board * b = (Board *)malloc(sizeof(Board));
	int i;
	b->row_array = (Row **)calloc(num_rows, sizeof(Row *));	//Array space
	for (i = 0; i < num_rows; i++)
		b->row_array[i] = createRow(row_size);
	b->num_rows = num_rows;
	b->row_size = row_size;
	b->colors = colors;
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
		for (j = 0; j < x; j++) {
			int code = b->row_array[i]->code_pegs[j];
			if (code == -1)
				printf("_ ");
			else 
				printf("%i ", code);
		}
		printf("\t\t");
		for (j = 0; j < x; j++) {
			int dcpt = b->row_array[i]->key_pegs[j]; 
			if (dcpt == RED) 
				printf("Re ");
			else if (dcpt == WHITE)
				printf("Wh ");
			else printf("__ ");
		}
		printf("\n");
	}
}

bool checkGuess(Board * b, int * a, int curr_guess) {
	bool is_match = true;
	int i, white = 0, red = 0, n = b->row_size;
	Row * r = b->row_array[curr_guess];
	int * ans = b->answer;

	bool is_checked[n];	//TODO: Checking for duplicates
	for (i = 0; i < n; i++)
		is_checked[i] = false;

	for (i = 0; i < n; i++) {	//RED
		r->code_pegs[i] = a[i];
		if (ans[i] != a[i])
			is_match = false;
		else red++;	//Correct position
	}
	if (!is_match) {	//WHITE
		for (i = 0; i < n; i++) {
			int j; 
			for (j = 0; j < n; j++) {
				if ((i == j) || (is_checked[j])) continue;	//TODO
				if (ans[i] == a[j]) {
					white++;
					is_checked[j] = true;
					break;	//Each answer is compared to entries until match is found.
				}
			}
		}
	}
	//white -= red;	//Correct letters minus position.
	for (i = 0; i < n; i++) {
		if (red > 0) {
			r->key_pegs[i] = RED;
			red--;
		} else if (white > 0) {
			r->key_pegs[i] = WHITE;
			white--;
		}
	}
	return is_match;
}

int main(void) {
	int num_colors = 6;
	int num_rows = 8;
	int row_size = 4;

	printf("Welcome to MasterMind->CodeMaker!\n");
	num_colors = input("Colors (leave blank for default 8): ", num_colors);
	num_rows = input("Number of guesses (leave blank for default 8): ", num_rows);
	row_size = input("Length of code (leave blank for default 4): ", row_size);
	printf("Colors: %i, Guesses: %i, Length: %i\n", num_colors, num_rows, row_size);

	Board * B = createBoard(num_rows, row_size, num_colors);

	int i;
	bool is_found = false;
	unsigned int a[row_size];
	char buffer[BUF_SIZE] = {'\0'};
	for (i = 0; i < row_size; i++)
		a[i] = -1;
	i = 0;
	while (i < num_rows) {
		printf("Current board: \n");
		printBoard(B);
		if (fgets(buffer, BUF_SIZE, stdin) == NULL) {
			printf("Please enter a guess\n");
			continue;
		}	//TODO: Variable size input
		if (sscanf(buffer, "%i %i %i %i", &a[0], &a[1], &a[2], &a[3]) != row_size) {
			printf("Please enter %i numbers\n", row_size);
			continue;
		}
		if ((is_found = checkGuess(B, a, i)) == true) {
			printf("Congratulations! You found the answer!\n");	//Check guess
			break;
		}
		int j;
		for (j = 0; j < row_size; j++)
			a[j] = 0;
		i++;
	}

	if (!is_found) {
		printf("You lost. Answer: ");
		printAns(B);
	}

	freeBird(B);
	return 0;
}
