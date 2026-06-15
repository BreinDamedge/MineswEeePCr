typedef enum { false, true } bool;
typedef enum { dirt, dug, flag } tileState;

typedef struct {
    int rows, cols, *counts, bombs, flags, numDirt;
    tileState *state;
    char *bar;
    bool bombed;    // if the bombs have been placed (initialized)
} Board;


void PrintBoard(const Board* b_);

Board* MakeBoard(const int r_, const int c_, const int numBombs_);
void InitializeBombs(Board* b_, const int r0_, const int c0_);

void FreeBoard(Board** b_);

int Dig(Board* b_, const int r_, const int c_);
int Mark(Board* b_, const int r_, const int c_);
void ClearEmpty(Board* b_, const int r_, const int c_);


void Reveal(Board* b_);

Board* LoadBoardCfg(const char* fname_);
