#include "game-manager.h"

GameManager::GameManager() {
    this->board = std::unique_ptr<Board>(new Board);
    this->current_player = 1;
    this->winner = 0;
}

GameManager::~GameManager() {}

void GameManager::get_user_input() {
    std::string r_input, c_input;
    int row, col;
    bool valid_data;
    bool valid_col, valid_row;

    valid_data = valid_col = valid_row = false;

    std::cout << "Turn: Player " << this->current_player << std::endl;
    while(!valid_data) {
        row = col = -1;
        std::cout << "Select row: ";
        std::getline(std::cin, r_input);

        std::cout << "Select column: ";
        std::getline(std::cin, c_input);

        try {
            row = std::stoi(r_input);
            valid_row = true;
        }
        catch(std::invalid_argument ia) {
            std::cout << "Invalid row\n";
            valid_row = false;
            continue;
        }
        
        try {
            col = std::stoi(c_input);
            valid_col = true;
        }
        catch(std::invalid_argument ia) {
            std::cout << "Invalid column\n";
            valid_col = false;
            continue;
        }

        if(row < 1 || row > 3) {
            std::cout << "Invalid row number\n";
            valid_row = false;
            continue;
        }
        if(col < 1 || col > 3) {
            std::cout << "Invalid column number\n";
            valid_col = false;
            continue;
        }

        if(this->board->get_mark_at(row-1, col-1) != '-') {
            valid_data = false;
            std::cout << "Invalid board position\n";
        }

        valid_data = valid_col && valid_row;
    }
    char mark = (this->current_player == 1 ? 'X' : 'O');
    this->board->set_board(row-1, col-1, mark);
}

bool GameManager::is_game_over() {
    char mark = (this->current_player == 1 ? 'X' : 'O');

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

    return false;
}

void GameManager::print_board() {
    this->board->print_board();
}

void GameManager::change_player() {
    this->current_player =
        (this->current_player == 1 ? 2 : 1);
}

char GameManager::get_winner_mark() {
    return (this->winner == 2 ? 'O' : 'X');
}

void GameManager::start_game() {
    while(true) {
        this->print_board();
        this->get_user_input();
        if(this->is_game_over())
            break;
        this->change_player();
    }

    std::cout << "\nGame ended!\n";
    std::cout << "Winner: Player " << this->winner
              << " ('" << this->get_winner_mark() << "')\n";
}
