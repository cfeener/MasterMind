/* Christopher Feener
 * This is the code-breaking side of MasterMind.
 */

#include "code.h"

int * makeGuess(Board * b, int i) {	//Random at first
	int n = b->row_size, mod = b->num_colors;
	int j;
	srand(time(0));
	int * a = calloc(n, sizeof(int));
	for (j = 0; j < n; j++) {
		a[j] = rand() % mod + 1;
	}
	return a;
}

int main(void) {
        int num_colors = 6;
        int num_rows = 8;
        int row_size = 4;
        int dup_allowed = false;

        printf("Welcome to MasterMind-> Code Breaker!\n");
        num_colors = input("Colors (leave blank for default 6): ", num_colors);
        num_rows = input("Number of guesses (leave blank for default 8): ", num_rows);
        row_size = input("Length of code (leave blank for default 4): ", row_size);
        dup_allowed = b_input("NO duplicates in answer (leave blank for default): ");
        printf("Colors: %i, Guesses: %i, Length: %i, ", num_colors, num_rows, row_size);
        if (dup_allowed)
                printf("Duplicates in answer\n");
        else printf("Duplicates NOT in answer\n");

	//Computer makes its own answer in set up.
        Board * B = createBoard(num_rows, row_size, num_colors, dup_allowed);

	//Computer finds that answer
	int i = 0;
	while (i < num_rows) {
		int * a = makeGuess(B, i);
		checkGuess(B, a, i);
		printBoard(B);
		i++;
	}

	freeBird(B);

	return 0;
}
