#ifndef CODE_H
#define CODE_H

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
	int num_colors;
	struct row ** row_array;	//Array of pointers
	bool dup_allowed;
	int * answer;
} Board;

typedef struct row {
	int row_size;	//Size of code_ and key_pegs arrays.
	int * code_pegs;	//Assigned to C colors
	int * key_pegs;	//Either empty, white, or red
} Row;

void swap(int * a, int * b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void setAnswer(Board * b) {
	int i, n = b->num_colors;
	b->answer = (int *)calloc(n, sizeof(int));
	srand(time(0));
	if (!b->dup_allowed) {	//Based on https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
		for (i = 0; i < n; i++) {	//Initial set of numbers
			b->answer[i] = i + 1;
		}
		for (i = n - 1; i > 0; i--)  {	//Shuffle numbers using random indices
			int j = rand() % (i + 1);
			swap(&b->answer[i], &b->answer[j]);
		}
	} else {	//Duplicates allowed? Just random numbers, then!
		for (i = 0; i < n; i++)
			b->answer[i] = rand() % n + 1;
	}
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

Board * createBoard(int num_rows, int row_size, int colors, bool dup_allowed) {
        Board * b = (Board *)malloc(sizeof(Board));
        int i;
        b->row_array = (Row **)calloc(num_rows, sizeof(Row *)); //Array space
        for (i = 0; i < num_rows; i++)
                b->row_array[i] = createRow(row_size);
        b->num_rows = num_rows;
        b->row_size = row_size;
        b->num_colors = colors;
        b->dup_allowed = dup_allowed;
        setAnswer(b);   //Randomly generated
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
        int val = deflt;        //Set initially to default.
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

        for (i = 0; i < n; i++) {       //RED
                r->code_pegs[i] = a[i]; //Insert value here.
                if (ans[i] != a[i])
                        is_match = false;
                else red++;     //Correct position
        }
        if (!is_match) {        //WHITE
                for (i = 0; i < n; i++) {
                        int j; 
                        for (j = 0; j < n; j++) {
                                if (ans[i] == a[j]) {
                                        white++;
                                        a[j] = -1;      //Change value to -inf
                                        break;  //Each answer is compared to entries until match is found.
                                }
                        }
                }
        }
        white -= red;   //Correct letters minus position.
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

bool b_input(char * str) {
        char temp[BUF_SIZE];
        char buffer[BUF_SIZE] = {'\0'};
        printf("%s", str);
        if (fgets(buffer, BUF_SIZE, stdin) != NULL) {
                if (sscanf(buffer, "%s", temp) == 1)
                        return true;
        }
        return false;
}

#endif
