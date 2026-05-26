#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_BAR 2048
#define BOMB -1




void PrintBoard(Board* b_) {
    // print the header --
    printf("Flags: %d\n", b_->flags);

    // print the grid --
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
    printf("%s", bar);
    for (int r = 0; r < b_->rows; r++) {
        printf("|");
        for (int c = 0; c < b_->cols; c++) {
            // printing counts
            if (b_->state[b_->cols*r+c] == dug) {
                if (b_->counts[b_->cols*r+c] == BOMB) {
                    printf("B|");
                } else {
                    if (b_->counts[r*b_->cols+c]) {
                        printf("%i|", b_->counts[r*b_->cols+c]);
                    } else {
                        printf(" |");
                    }
                }
            } else if (b_->state[b_->cols*r+c] == flag) {
                printf("F|");
            } else {
                // checkered appearance
                if ((r+c)%2) {
                    printf(".|");
                } else {
                    printf("X|");
                }
            }

        }
        printf("\n");
        printf("%s", bar);
    }
}


Board* MakeBoard(int r_, int c_, int numBombs_) {
    Board* newBoard = malloc(sizeof(Board));
    if (!newBoard) { return NULL; }
    newBoard->rows  = r_;
    newBoard->cols  = c_;
    newBoard->bombs = numBombs_;
    newBoard->flags = numBombs_;

    // allocate the 2darray
    newBoard->state = malloc(sizeof(tileState)*r_*c_);
    newBoard->counts = malloc(sizeof(int)*r_*c_);   // for best practice you'd check this pointer. can't remember what you're supposed to do if it fails tho. you'd clean up as best you could and then shutdown the program probably. you could retry. doesn't matter rn tho.
    for (int i = 0; i<r_*c_; i++) {
        newBoard->counts[i] = 0;
        newBoard->state[i] = dirt;
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


// modify the state val at r_ c_. return 0 unless you dug a bomb, then return 1
int Dig(Board* b_, int r_, int c_) {
    if (b_->state[b_->cols*r_+c_] == flag) {
        // TODO some message to let you know that you've dug a spot that's already flagged
        return 0;
    }
    b_->state[b_->cols*r_+c_] = dug;
    return b_->counts[b_->cols*r_+c_] == BOMB;
}


// modify the state val at r_ c_ to add a flag. return 0 unless you are out of flags
int Mark(Board* b_, int r_, int c_) {
    if (b_->state[b_->cols*r_+c_] == flag) {
        b_->flags++;
        b_->state[b_->cols*r_+c_] = dirt;
        return 0;
    } else {
        if (b_->flags > 0) {
            b_->flags--;
            b_->state[b_->cols*r_+c_] = flag;
            return 0;
        }
    }
    return 1;
}

void Reveal(Board* b_) {
    for (int i = 0; i < b_->rows*b_->cols; i++) {
        b_->state[i] = dug;
    }
}

