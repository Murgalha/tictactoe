#include <memory>
#include "board.h"

Board::Board() {
    this->_board_size = 3;
    this->mat = char_matrix(this->_board_size,
                            std::vector<char>(this->_board_size, '-'));
}

Board::~Board() {}

void Board::print_board() {
    for(int i = 0; i < this->_board_size; i++) {
        for(int j = 0; j < this->_board_size; j++) {
            std::cout << this->mat[i][j];
        }
        std::cout << std::endl;
    }
}

void Board::set_board(int row, int col, char mark) {
    (this->mat)[row][col] = mark;
}

int Board::board_size() {
    return this->_board_size;
}

char Board::get_mark_at(int row, int col) {
    return (this->mat)[row][col];
}

bool Board::is_full() {
    for(int i = 0; i < this->_board_size; i++) {
        for(int j = 0; j < this->_board_size; j++) {
            if((this->mat)[i][j] == '-')
                return false;
        }
    }
    return true;
}
