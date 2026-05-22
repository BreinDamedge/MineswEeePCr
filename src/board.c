#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_BAR 2048
#define BOMB -1




void PrintBoard(Board* b_) {
    // make the bar
    int barLen = b_->cols*(2)+3;
    if (barLen > MAX_BAR) { printf("BOARD OVER MAX EXPECTED SIZE!!!\n"); }
    char bar[MAX_BAR];   // needs to be null terminated
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
            // printing counts
            if (b_->counts[b_->cols*r+c] == BOMB) {
                printf("B|");
            } else {
                printf("%i|", b_->counts[r*b_->cols+c]);
            }

            // checkered appearance
            // if ((r+c)%2) {
            //     printf(".|");
            // } else {
            //     printf("X|");
            // }
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
    newBoard->dug = malloc(sizeof(bool)*r_*c_);
    newBoard->counts = malloc(sizeof(int)*r_*c_);   // for best practice you'd check this pointer. can't remember what you're supposed to do if it fails tho. you'd clean up as best you could and then shutdown the program probably. you could retry. doesn't matter rn tho.
    for (int i = 0; i<r_*c_; i++) {
        newBoard->counts[i] = 0;
        newBoard->dug[i] = false;
    }

    // assign bombs
    int r, c;
    for (int _ = 0; _ < numBombs_; _++) {
        // random x & y
        r = rand() % r_;
        c = rand() % c_;

        // set bomb pos in grid to BOMB
        if (newBoard->counts[r*c_+c] == BOMB) {_--; } // add another loop bc ur a bozo
        else { newBoard->counts[r*c_+c] = BOMB; }
    }

    // counts
    for (int r = 0; r < r_; r++) {
        for (int c = 0; c < c_; c++) {
            if (newBoard->counts[r*c_+c] == BOMB) { continue; }
            for (int ro = BOMB; ro < 2; ro++) {
                for (int co = BOMB; co < 2; co++) {
                    if (r+ro >= 0 && c+co >= 0 && r+ro < r_ && c+co < c_) {
                        if (newBoard->counts[(r+ro)*c_+(c+co)] == BOMB && newBoard->counts[r*c_+c] != BOMB) {
                            newBoard->counts[r*c_+c]++;
                        }
                    }
                }
            }
       }
    }

    return newBoard;
}


void FreeBoard(Board** b_) {
    Board* b = *b_;
    free(b->counts);
    free(b);
    b = NULL;
}

