#include "gamemanager.h"

GameManager::GameManager() {
    this->board = std::unique_ptr<Board>(new Board);
    this->current_player = 1;
    this->winner = -1;
}

GameManager::~GameManager() {}

bool GameManager::is_game_over() {
    char mark = this->get_player_mark();

    for(int i = 0; i < this->board->board_size(); i++)
        if(this->board->get_mark_at(i, 0) == mark &&
           this->board->get_mark_at(i, 1) == mark &&
           this->board->get_mark_at(i, 2) == mark) {
            this->winner = this->current_player;
            return true;
        }
    for(int i = 0; i < this->board->board_size(); i++)
        if(this->board->get_mark_at(0, i) == mark &&
           this->board->get_mark_at(1, i) == mark &&
           this->board->get_mark_at(2, i) == mark) {
            this->winner = this->current_player;            
            return true;
        }
    if(this->board->get_mark_at(0, 0) == mark &&
       this->board->get_mark_at(1, 1) == mark &&
       this->board->get_mark_at(2, 2) == mark) {
        this->winner = this->current_player;
        return true;
    }
    if(this->board->get_mark_at(0, 2) == mark &&
       this->board->get_mark_at(1, 1) == mark &&
       this->board->get_mark_at(2, 0) == mark) {
        this->winner = this->current_player;
        return true;
    }

    if(this->board->is_full() && this->winner == -1) {
        this->winner = 0;
        return true;
    }
    
    return false;
}

void GameManager::print_board() {
    this->board->print_board();
}

bool GameManager::game_ended() {
    return (this->winner >= 0 ? true : false);
}

void GameManager::change_player() {
    this->current_player =
        (this->current_player == 1 ? 2 : 1);
}

char GameManager::get_player_mark() {
    return (this->current_player == 1 ? 'X' : 'O');
}

char GameManager::get_winner_mark() {
    return (this->winner == 1 ? 'X' : 'O');
}

void GameManager::set_turn(int row, int col, char mark) {
    this->board->set_board(row, col, mark);
    if(!this->is_game_over())
        this->change_player();
}
