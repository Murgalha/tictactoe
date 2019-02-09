#include <cstdlib>
#include <climits>
#include <algorithm>
#include "ai.h"
#include "board.h"

AI::AI(Board *b, int d) {
    this->board = b;
    this->difficulty = d;
}

std::vector<BOARD_POS> AI::get_empty_positions(Board b) {
    std::vector<BOARD_POS> positions;

    for(int i = 0; i < b.board_size(); i++) {
        for(int j = 0; j < b.board_size(); j++) {
            if(b.get_mark_at(i, j) == '-') {
                BOARD_POS bp;
                bp.row = i;
                bp.column = j;
                positions.push_back(bp);
            }
        }
    }
    return positions;
}

int AI::evaluate_board(Board b) {
    for(int i = 0; i < b.board_size(); i++) {
        if(b.get_mark_at(i, 0) == 'X' &&
           b.get_mark_at(i, 1) == 'X' &&
           b.get_mark_at(i, 2) == 'X')
            return 10;
        if(b.get_mark_at(i, 0) == 'O' &&
           b.get_mark_at(i, 1) == 'O' &&
           b.get_mark_at(i, 2) == 'O')
            return -10;
    }

    for(int i = 0; i < b.board_size(); i++) {
        if(b.get_mark_at(0, i) == 'X' &&
           b.get_mark_at(1, i) == 'X' &&
           b.get_mark_at(2, i) == 'X')
            return 10;
        if(b.get_mark_at(0, i) == 'O' &&
           b.get_mark_at(1, i) == 'O' &&
           b.get_mark_at(2, i) == 'O')
            return -10;
    }

    if(b.get_mark_at(0, 0) == 'X' &&
       b.get_mark_at(1, 1) == 'X' &&
       b.get_mark_at(2, 2) == 'X')
        return 10;
    if(b.get_mark_at(0, 0) == 'O' &&
       b.get_mark_at(1, 1) == 'O' &&
       b.get_mark_at(2, 2) == 'O')
        return -10;

    if(b.get_mark_at(0, 2) == 'X' &&
       b.get_mark_at(1, 1) == 'X' &&
       b.get_mark_at(2, 0) == 'X')
        return 10;
    if(b.get_mark_at(0, 2) == 'O' &&
       b.get_mark_at(1, 1) == 'O' &&
       b.get_mark_at(2, 0) == 'O')
        return -10;
    return 0;
}

int AI::minimax(Board b, int depth, bool is_maximizing) {
    int score = evaluate_board(b);
    std::vector<BOARD_POS> empty = this->get_empty_positions(b);

    if(score == 10)
        return score;
    else if(score == -10)
        return score;
    else if(b.is_full())
        return 0;

    if(is_maximizing) {
        int best = INT_MIN;
        for(int i = 0; i < empty.size(); i++) {
            Board tmp = b;
            tmp.set_board(empty[i].row, empty[i].column, 'X');

            best = std::max(best, minimax(tmp, depth+1, !is_maximizing));
        }
        return best;
    }
    else {
        int best = INT_MAX;
        for(int i = 0; i < empty.size(); i++) {
            Board tmp = b;
            tmp.set_board(empty[i].row, empty[i].column, 'O');

            best = std::min(best, minimax(tmp, depth+1, !is_maximizing));
        }
        return best;
    }
}

BOARD_POS AI::find_best_move() {
    std::vector<BOARD_POS> empty = this->get_empty_positions(*(this->board));
    int best_value = INT_MAX;
    BOARD_POS best_move;
    best_move.row = best_move.column = -1;

    for(int i = 0; i < empty.size(); i++) {
        Board tmp = *(this->board);
        tmp.set_board(empty[i].row, empty[i].column, 'O');
        int move_value = this->minimax(tmp, 0, true);

        if(move_value < best_value) {
            best_move.row = empty[i].row;
            best_move.column = empty[i].column;
            best_value = move_value;
        }
    }
    return best_move;
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
        return this->find_best_move();
    }
}
