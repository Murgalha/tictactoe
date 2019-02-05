#include "tictactoegui.h"

TicTacToeGUI::TicTacToeGUI() {
    this->window = std::unique_ptr<sf::RenderWindow>
        (new sf::RenderWindow(sf::VideoMode(600, 600),
                              "Tic Tac Toe", sf::Style::Close));
    this->gm = std::unique_ptr<GameManager>(new GameManager);
    this->font = std::unique_ptr<sf::Font>(new sf::Font);
    this->mark = std::unique_ptr<sf::Text>(new sf::Text);

    this->window->clear(sf::Color::White);
    this->font->loadFromFile("fonts/TruenoBd.otf");

    this->mark->setFont(*(this->font));
    this->mark->setFillColor(sf::Color::Black);
    this->mark->setCharacterSize(100);    
}

void TicTacToeGUI::draw_board() {
    int board_margin = 30;
    // each line has 2 vertices and there are 4 lines needed 
    std::unique_ptr<sf::VertexArray> lines(new sf::VertexArray(sf::Lines, 8));

    (*lines)[0].position = sf::Vector2f(window->getSize().x * (1.0/3.0),
                                        board_margin);    
    (*lines)[1].position = sf::Vector2f(window->getSize().x * (1.0/3.0),
                                     window->getSize().y - board_margin);
    (*lines)[2].position = sf::Vector2f(window->getSize().x * (2.0/3.0),
                                        board_margin);
    (*lines)[3].position = sf::Vector2f(window->getSize().x * (2.0/3.0),
                                     window->getSize().y - board_margin);
    (*lines)[4].position = sf::Vector2f(board_margin,
                                        window->getSize().y * (1.0/3.0));
    (*lines)[5].position = sf::Vector2f(window->getSize().x - board_margin,
                                        window->getSize().y * (1.0/3.0));
    (*lines)[6].position = sf::Vector2f(board_margin,
                                        window->getSize().y * (2.0/3.0));
    (*lines)[7].position = sf::Vector2f(window->getSize().x - board_margin,
                                        window->getSize().y * (2.0/3.0));
    for(int i = 0; i < 8; i++) {
        (*lines)[i].color = sf::Color::Black;
    }
    
    this->window->draw(*lines);
}

void TicTacToeGUI::draw_mark(int pos_x, int pos_y, char mark) {
    this->mark->setPosition(pos_x, pos_y);
    this->mark->setString(std::string(1, mark));
    this->window->draw(*(this->mark));
}

void TicTacToeGUI::process_turn(BOARD_POS bp) {
    if(this->gm->get_mark_at(bp.row, bp.column) == '-') {
        int text_pos_x, text_pos_y;
        int first_col = this->window->getSize().x * (1.0/3.0);
        int second_col = this->window->getSize().x * (2.0/3.0);
        int first_row = this->window->getSize().y * (1.0/3.0);
        int second_row = this->window->getSize().y * (2.0/3.0);
        int x = bp.column, y = bp.row;

        if(y == 0) {
            text_pos_y = first_row/2;
        }
        else if(y == 1) {
            text_pos_y = (first_row+second_row)/2;
        }
        else {
            text_pos_y = (second_row+this->window->getSize().y)/2;
        }

        if(x == 0) {
            text_pos_x = first_col/2;
        }
        else if(x == 1) {
            text_pos_x = (first_col+second_col)/2;
        }
        else {
            text_pos_x = (second_col+this->window->getSize().x)/2;
        }
        // margin to fit center of board squares
        int margin_x = 35, margin_y = 60;
        char mark = this->gm->get_player_mark();
        this->gm->set_turn(bp.row, bp.column, mark);
        this->draw_mark(text_pos_x - margin_x, text_pos_y - margin_y, mark);

        // DEBUG
        this->gm->print_board();
    }
}

void TicTacToeGUI::process_ai_turn() {
    if(this->gm->get_current_player() == 2) {
        BOARD_POS bp = this->gm->get_ai_move();
        this->process_turn(bp);
    }
}

BOARD_POS TicTacToeGUI::process_mouse_click(int x, int y) {
    if(this->gm->get_current_player() == 1) {
        int first_col = this->window->getSize().x * (1.0/3.0);
        int second_col = this->window->getSize().x * (2.0/3.0);
        int first_row = this->window->getSize().y * (1.0/3.0);
        int second_row = this->window->getSize().y * (2.0/3.0);
        int input_col, input_row, text_pos_x, text_pos_y;
        
        if(y <= first_row) {
            input_row = 0;
        }
        else if(y <= second_row) {
            input_row = 1;
        }
        else {
            input_row = 2;
        }

        if(x <= first_col) {
            input_col = 0;
        }
        else if(x <= second_col) {
            input_col = 1;
        }
        else {
            input_col = 2;
        }

        std::cout << "Mouse clicked on row " << input_row+1 <<
            " and column " << input_col+1 << std::endl;

        BOARD_POS bp;
        bp.row = input_row;
        bp.column = input_col;

        return bp;
    }
}

void TicTacToeGUI::window_loop() {
    while(this->window->isOpen()) {
        this->window->setActive();
        
        // Event processing
        sf::Event event;

        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                this->window->close();
            else if(event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                int xPos = event.mouseButton.x;
                int yPos = event.mouseButton.y;
                BOARD_POS bp = process_mouse_click(xPos, yPos);
                this->process_turn(bp);
                this->process_ai_turn();
            }
        }
        // Activate the window for OpenGL rendering
        this->draw_board();
        
        // OpenGL drawing commands go here...
        // End the current frame and display its contents on screen
        this->window->display();

        if(this->gm->game_ended()) {
            // draw winner
            this->window->close();
        }
    }    
}

int main() {
    std::unique_ptr<TicTacToeGUI> tttg =
        std::unique_ptr<TicTacToeGUI>(new TicTacToeGUI);
    tttg->window_loop();
}
