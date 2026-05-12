/* 5.11.2026 - MineswEeePCr
 * here's our lovely little minesweeper project
 */

#include <stdio.h>
#include "board.h"

int main() {
    printf("hello world!\n");

    Board b;
    b.rows = 5;
    b.cols = 4;
    printf("rows: %i\ncols: %i\n", b.rows, b.cols);

    return 0;
}
