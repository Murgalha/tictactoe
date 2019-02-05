#include <cstdlib>
#include "ai.h"

AI::AI(Board *b, int d) {
    this->board = b;
    this->difficulty = d;
}

 BOARD_POS AI::get_move() {
    std::vector<int> free_pos;
    int b_size = this->board->board_size();
    BOARD_POS ret;
    srand(time(NULL));

    if(this->difficulty == EASY) {
        for(int i = 0; i < b_size*b_size; i++) {
            if(this->board->get_mark_at(i / b_size, i % b_size) == '-') {
                free_pos.push_back(i);
            }
        }

        // choose empty space
        int rand_index = rand() % free_pos.size(); 
        ret.row = free_pos[rand_index] / b_size;
        ret.column = free_pos[rand_index] % b_size;

        return ret;
    }
    else if(this->difficulty == IMPOSSIBLE) {
        // make algorithm
    }
}
