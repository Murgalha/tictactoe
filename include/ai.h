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
    std::vector<BOARD_POS> get_empty_positions(Board);
    int minimax(Board, int, bool);
    BOARD_POS find_best_move();
    int evaluate_board(Board);
public:
    AI(Board *, int);
    void set_difficulty(int);
    BOARD_POS get_move();
};

#endif
