#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include <iostream>

typedef std::vector< std::vector<char> > char_matrix;

class Board {
public:
    Board();
    ~Board();
    void print_board();
    void set_board(int, int, char);
    int board_size();
    char get_mark_at(int, int);
    bool is_full();
private:
    char_matrix mat;
    int _board_size;
};

#endif
