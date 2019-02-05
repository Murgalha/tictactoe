#ifndef _AI_H_
#define _AI_H_

#include <memory>
#include "board.h"

enum {
    EASY,
    IMPOSSIBLE
};

class AI {
private:
    int difficulty;
    Board *board;
public:
    AI(Board *, int);
    void set_difficulty(int);
    BOARD_POS get_move();
};

#endif
