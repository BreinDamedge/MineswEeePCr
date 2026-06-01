typedef enum { false, true } bool;
typedef enum { dirt, dug, flag } tileState;

typedef struct {
    int rows, cols, *counts, bombs, flags, numDirt;
    tileState *state;
    char *bar;
    bool bombed;    // if the bombs have been placed (initialized)
} Board;


void PrintBoard(Board* b_);

Board* MakeBoard(int r_, int c_, int numBombs_);
void InitializeBombs(Board* b_, int r0_, int c0_);

void FreeBoard(Board** b_);

int Dig(Board* b_, int r_, int c_);
int Mark(Board* b_, int r_, int c_);
void ClearEmpty(Board* b_, int r_, int c_);


void Reveal(Board* b_);

