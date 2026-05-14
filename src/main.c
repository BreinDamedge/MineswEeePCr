/* 5.11.2026 - MineswEeePCr
 * here's our lovely little minesweeper project
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

int main() {
    printf("hello world!\n");
    srand(time(NULL));

    // initialize the board
    Board* b = MakeBoard(10, 10, 20);
    if (!b) {
        printf("b address is null, exiting.\n");
        return 1;
    }

    // printf("rows: %i\ncols: %i\n", b->rows, b->cols);
    PrintBoard(b);

    // loop
    // display it (figure that out)
    // get user input
    // mark/break spot

    FreeBoard(&b);
    return 0;
}
