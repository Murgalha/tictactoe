#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <memory>
#include "board.h"
#include "ai.h"

class GameManager {
public:
    GameManager();
    ~GameManager();
    char get_winner_mark();
    char get_player_mark();
    void set_turn(int, int, char);
    void print_board();
    bool game_ended();
    int get_current_player();
    char get_mark_at(int, int);
    BOARD_POS get_ai_move();
private:
    // functions
    void change_player();
    bool is_game_over();
    
    // variables
    std::unique_ptr<Board> board;
    std::unique_ptr<AI> ai;
    int current_player;
    int winner;
};

#endif
