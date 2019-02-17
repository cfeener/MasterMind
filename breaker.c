/* Christopher Feener
 * This is the code-breaking side of MasterMind.
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

	freeBird(B);

	return 0;
}
