/* 6.13.2026 - MineswEeePCr - test.c
 * test file reading serialized games
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include <unistd.h> // sleep
#define INPUT_LEN 10



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
    Board* b = MakeBoard(5, 5, 3);
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
            // !!! Allowing marking before the bombs have been placed should be fine. might cause weird behavior with clearing free tiles but shouldn't otherwise affect bomb generation.
            if (Mark(b, R, C)) {
                // ur out of flags
            }
        } else if (M == 'd') {
            if (b->bombed){
                if (Dig(b, R, C)) {
                    // loss
                    Reveal(b);
                    clearScreen();
                    printf("You Lose. :[\n");
                    PrintBoard(b);
                    break;
                } 
                
            } else {
                InitializeBombs(b, R, C);
            }
            
        } 

        // check win condition
        if (b->numDirt == 0 && b->flags == 0) {
            clearScreen();
            printf("You Win!!! :]\n");
            PrintBoard(b);
            break;
        }
        
    }


    FreeBoard(&b);
    return 0;
}
