#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_CONFIG_LINE_LENGTH 32
#define BOMB -1




void PrintBoard(const Board* b_) {
    // print the header --
    printf("Flags: %d, Dirt: %d\n", b_->flags, b_->numDirt);

    // print the column numbers
    printf("  ");
    for (int i = 0; i < b_->cols; i++) { printf(" %i", i%10); }
    printf("\n");

    // print the grid --
    printf("  %s", b_->bar);
    for (int r = 0; r < b_->rows; r++) {
        // print row numbers
        printf("%i |", r%10);
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
        printf("  %s", b_->bar);
    }
}


Board* MakeBoard(const int r_, const int c_, const int numBombs_) {
    Board* newBoard = malloc(sizeof(Board));
    if (!newBoard) { return NULL; }
    newBoard->rows  = r_;
    newBoard->cols  = c_;
    newBoard->bombs = numBombs_;
    newBoard->flags = numBombs_;
    newBoard->numDirt = r_*c_;
    newBoard->bombed = false;

    // make the bar (used in PrintBoard()
    int barLen = c_*(2)+3;
    newBoard->bar = malloc(sizeof(char)*barLen);
    for (int c = 0; c < barLen; c+=2) {
        newBoard->bar[c]   = '+';
        newBoard->bar[c+1] = '-';
    }
    newBoard->bar[barLen-2] = '\n';
    newBoard->bar[barLen-1] = 0;

    // allocate the 2darray
    newBoard->state = malloc(sizeof(tileState)*r_*c_);
    newBoard->counts = malloc(sizeof(int)*r_*c_);   // for best practice you'd check this pointer. can't remember what you're supposed to do if it fails tho. you'd clean up as best you could and then shutdown the program probably. you could retry. doesn't matter rn tho.
    for (int i = 0; i<r_*c_; i++) {
        newBoard->counts[i] = 0;
        newBoard->state[i] = dirt;
    }
    
    return newBoard;
}


// r/c0_ are the location of the first broken spot.
void InitializeBombs(Board* b_, const int r0_, const int c0_) {
    int r, c;
    for (int _ = 0; _ < b_->bombs; _++) {
        // random x & y
        r = rand() % b_->rows;
        c = rand() % b_->cols;

        // set bomb pos in grid to BOMB
        if ( b_->counts[r*b_->cols+c] == BOMB || (r == r0_ && c == c0_) ) {_--; } // add another loop bc ur a bozo (placed a bomb where one exists, or in the initially cleared spot)
        else { b_->counts[r*b_->cols+c] = BOMB; }
    }

    // counts
    for (int r = 0; r < b_->rows; r++) {
        for (int c = 0; c < b_->cols; c++) {
            if (b_->counts[r*b_->cols+c] == BOMB) { continue; }
            for (int ro = BOMB; ro < 2; ro++) {
                for (int co = BOMB; co < 2; co++) {
                    if (r+ro >= 0 && c+co >= 0 && r+ro < b_->rows && c+co < b_->cols) {
                        if (b_->counts[(r+ro)*b_->cols+(c+co)] == BOMB && b_->counts[r*b_->cols+c] != BOMB) {
                            b_->counts[r*b_->cols+c]++;
                        }
                    }
                }
            }
        }
    }

   // mark r/c0 as dug 
   b_->state[r0_*b_->cols+c0_] = dug;
   b_->numDirt--;
   // mark the bombs as initialized
   b_->bombed = true;
   if (b_->counts[r0_*b_->cols+c0_] == 0) { ClearEmpty(b_, r0_, c0_); }
}


void FreeBoard(Board** b_) {
    Board* b = *b_;
    free(b->counts);
    free(b);
    b = NULL;
}


// modify the state val at r_ c_. return 0 unless you dug a bomb, then return 1
int Dig(Board* b_, const int r_, const int c_) {
    if (b_->state[b_->cols*r_+c_] == flag) {
        // TODO some message to let you know that you've dug a spot that's already flagged
        return 0;
    }
    if (b_->state[b_->cols*r_+c_] == dirt) {
        b_->state[b_->cols*r_+c_] = dug;
        b_->numDirt--;
    }
    if (b_->counts[b_->cols*r_+c_] == 0 ) { ClearEmpty(b_, r_, c_); }
    return b_->counts[b_->cols*r_+c_] == BOMB;
}


// modify the state val at r_ c_ to add a flag. return 0 unless you are out of flags
int Mark(Board* b_, const int r_, const int c_) {
    if (b_->state[b_->cols*r_+c_] == flag) {
        b_->flags++;
        b_->numDirt++;
        b_->state[b_->cols*r_+c_] = dirt;
        return 0;
    } else {
        if (b_->flags > 0 && b_->state[b_->cols*r_+c_] == dirt) {
            b_->flags--;
            b_->numDirt--;
            b_->state[b_->cols*r_+c_] = flag;
            return 0;
        }
    }
    return 1;
}


void ClearEmpty(Board* b_, const int r_, const int c_) {
    // only enter this function if counts at r_ c_ is 0
    // loop through neighbors
    for (int ro = -1; ro < 2; ro++) {
        for (int co = -1; co < 2; co++) {
            if (ro == 0 && co == 0) { continue; }   // ur back on this square so skip
            // if neighbor is in bounds
            if (r_+ro >= 0 && c_+co >= 0 && r_+ro < b_->rows && c_+co < b_->cols) {
                // recurse if needed
                if ((b_->counts[(r_+ro)*b_->cols+(c_+co)] == 0) &&
                    (b_->state[(r_+ro)*b_->cols+(c_+co)] == dirt)) {
                    b_->state[(r_+ro)*b_->cols+(c_+co)] = dug;  // dig before you recurse to stop infiniteness
                    b_->numDirt--;
                    ClearEmpty(b_, r_+ro, c_+co);
                } else if (b_->state[(r_+ro)*b_->cols+(c_+co)] == dirt) {
                    b_->state[(r_+ro)*b_->cols+(c_+co)] = dug;  // dig to reveal numbers
                    b_->numDirt--;
                }
            }
        }
    }
}


void Reveal(Board* b_) {
    for (int i = 0; i < b_->rows*b_->cols; i++) {
        b_->state[i] = dug;
    }
}


/* read a board config file and then return a Board* with those bombs and stuff. */
Board* LoadBoardCfg(const char* fname_) {
    FILE *f;
    char buff[MAX_CONFIG_LINE_LENGTH];
    bool firstLine = true;
    Board* b;
    f = fopen(fname_, "r");
    if (file == NULL) { /* handle error ... */ }
    int r, c, bombs;
    while (fgets(buff, MAX_CONFIG_LINE_LENGTH, f) != NULL) {
        if (firstLine) {
            sscanf(buff, "%d %d %d", &r, &c, &bombs);
            b = MakeBoard(r, c, bombs);
            firstLine = false;
        } else {
            // ...
            sscanf(buff, "%d %d", &rows, &cols);
            // set bombs up...
            b->counts[rows*b->cols+cols] = BOMB;
        }
    }
    fclose(f);
    // initialize the counts

}
