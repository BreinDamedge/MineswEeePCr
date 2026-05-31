/* 5.11.2026 - MineswEeePCr - main.c
 * here's our lovely little minesweeper project
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include <unistd.h> // sleep




void clearScreen() {
    // \033[H moves cursor to top-left; \033[J clears the screen
    printf("\033[H\033[J");
}


int main() {
    srand(time(NULL));
    // get board size
    int R,C;
    char M;
    // printf("board size (rows cols)\n");
    // scanf("%d %d", &R, &C);

    // initialize the board
    Board* b = MakeBoard(10, 10, 10);
    if (!b) {
        printf("b address is null, exiting.\n");
        return 1;
    }

    // loop
    // display it (figure that out)
    while (true) {
        clearScreen();
        PrintBoard(b);

        // get user input
        scanf("%c %d %d", &M, &R, &C);
        // TODO bounds check
        // mark/dig spot
        if (M == 'm') {
            if (Mark(b, R, C)) {
                // ur out of flags
            }
        } else if (M == 'd') {
            if (b->bombed){
                if (Dig(b, R, C)) {
                    Reveal(b);
                    clearScreen();
                    printf("You Lose :[\n");
                    PrintBoard(b);
                    break;
                } 
            } else {
                InitializeBombs(b, R, C);
            }
            
        } 
        
    }


    FreeBoard(&b);
    return 0;
}
