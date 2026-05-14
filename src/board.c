#include "board.h"
#include <stdio.h>
#include <stdlib.h>

void PrintBoard(Board* b_) {
    // make the bar
    int barLen = b_->cols*(2)+3;
    char bar[barLen];   // needs to be null terminated
    for (int c = 0; c < barLen; c+=2) {
        bar[c]   = '+';
        bar[c+1] = '-';
    }
    bar[barLen-2] = '\n';
    bar[barLen-1] = 0;

    // print the grid
    // TODO: state of squares affecting print out
    printf("%s", bar);
    for (int r = 0; r < b_->rows; r++) {
        printf("|");
        for (int c = 0; c < b_->cols; c++) {
            // checkered appearance
            if ((r+c)%2) {
                printf(".|");
            } else {
                printf("o|");
            }
        }
        printf("\n");
        printf("%s", bar);
    }
}


Board* MakeBoard(int r_, int c_, int numBombs_) {
    Board* newBoard = malloc(sizeof(Board));
    if (!newBoard) { return NULL; }
    newBoard->rows = r_;
    newBoard->cols = c_;

    // allocate the 2darray
    // TODO: redo this as contiguos memory
    newBoard->counts = malloc(sizeof(int*)*r_);

    for (int r = 0; r < r_; r++) {
        newBoard->counts[r] = calloc(sizeof(int)*c_, 0);
    }

    // assign bombs
    for (int _ = 0; _ < numBombs_; _++) {
        // random x & y
        int r, c;
        r = rand() % r_;
        c = rand() % c_;

        // set bomb pos in grid to -1
        newBoard->counts[r][c] = -1;
    }

    return newBoard;
}


void FreeBoard(Board** b_) {
    Board* b = *b_;
    for (int r = 0; r < b->rows; r++) {
        printf("there's a bug in here :]\n");
        free(b->counts[r]);
    }
    free(b->counts);
    free(b);
    b = NULL;
}

