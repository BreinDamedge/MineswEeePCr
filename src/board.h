typedef struct {
    int rows, cols, *counts;
} Board;

typedef enum {EMPTY, DIRT, FLAG} TileStatus;

void PrintBoard(Board* b_);

Board* MakeBoard(int r_, int c_, int numBombs_);

void FreeBoard(Board** b_);
