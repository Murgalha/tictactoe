#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <memory>
#include "board.h"

class GameManager {
public:
    GameManager();
    ~GameManager();
    void start_game();
private:
    char get_winner_mark();
    void change_player();
    void get_user_input();
    bool is_game_over();
    void print_board();
    std::unique_ptr<Board> board;
    int current_player;
    int winner;
};

#endif
