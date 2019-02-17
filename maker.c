/* Christopher Feener
 * Mastermind program
 * Started on 3 February 2019
 * This program is the codemaker currently.
 */

#include "code.h"

int main(void) {
	int num_colors = 6;
	int num_rows = 8;
	int row_size = 4;
	int dup_allowed = false;

	printf("Welcome to MasterMind->CodeMaker!\n");
	num_colors = input("Colors (leave blank for default 8): ", num_colors);
	num_rows = input("Number of guesses (leave blank for default 8): ", num_rows);
	row_size = input("Length of code (leave blank for default 4): ", row_size);
	dup_allowed = b_input("NO duplicates in answer (leave blank for default): ");
	printf("Colors: %i, Guesses: %i, Length: %i, ", num_colors, num_rows, row_size);
	if (dup_allowed)
		printf("Duplicates in answer\n");
	else printf("Duplicates NOT in answer\n");

	Board * B = createBoard(num_rows, row_size, num_colors, dup_allowed);

	int i;
	bool is_found = false;
	unsigned int a[row_size];	//Guess cannot be negative! (-1 = blank)
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
		if (sscanf(buffer, "%i %i %i %i %i %i %i %i", 
			&a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6], &a[7]) != row_size) {
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
