/* Christopher Feener
 * This is the code-breaking side of MasterMind.
 */

#include "code.h"

int * makeGuess(Board * b, int i) {	//Random at first
	int n = b->row_size, mod = b->num_colors;
	int * a = (int *)calloc(n, sizeof(int));
	if (i == 0) {	//First guess.
		int j;
		for (j = 0; j < n; j++) 
			a[j] = j;
	} else {	//Using Fisher-Yates shuffle. 
		int j;
		for (j = 0; j < n; j++)
			a[j] = j + 1;
		for (j = n - 1; j > 0; j--) {
			int k = rand() % (j + 1);
			swap(&a[j], &a[k]);
		}
	}
	return a;
}

/* Note: No idea how to go forward other than making giant array of possible answers,
	then going through them every time a guess is made.
 *
 */
/*void analyzeResponse(Board * b) {	//TODO: Rule out possible guesses out of 1296?!
	printf("Coming soon\n");
	return;
}*/

int main(void) {
        int num_colors = 6;
        int num_rows = 8;
        int row_size = 4;
        int dup_allowed = false;

	srand(time(0));	//Allows for different values for each iteration.

        printf("Welcome to MasterMind-> Code Breaker!\n");
	/* Base algorithm should work on default settings as shown on Wiki: 
		https://en.wikipedia.org/wiki/Mastermind_(board_game)#Algorithms*/

	//Computer makes its own answer in set up.
        Board * B = createBoard(num_rows, row_size, num_colors, dup_allowed);

	//Computer finds that answer
	int i = 0;
	bool is_won = false;
	while (i < num_rows) {
		int * a = makeGuess(B, i);
		if (checkGuess(B, a, i)) {
			is_won = true;
			break;
		}
		//analyzeResponse(B);
		printBoard(B);
		i++;
	}

	if (is_won)
		printf("I won!\n");
	else printf("I lost.\n");

	freeBird(B);

	return 0;
}
