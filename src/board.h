typedef enum { false, true } bool;
typedef enum { dirt, dug, flag } tileState;

typedef struct {
    int rows, cols, *counts, bombs, flags;
    tileState *state;
} Board;


void PrintBoard(Board* b_);

Board* MakeBoard(int r_, int c_, int numBombs_);

void FreeBoard(Board** b_);

int Dig(Board* b_, int r_, int c_);
int Mark(Board* b_, int r_, int c_);

void Reveal(Board* b_);

