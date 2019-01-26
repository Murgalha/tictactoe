#ifndef _TTTGUI_H_
#define _TTTGUI_H_

#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gamemanager.h"

class TicTacToeGUI {
public:
    TicTacToeGUI();
    void window_loop();
private:
    // variables
    std::unique_ptr<GameManager> gm;
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<sf::Font> font;
    std::unique_ptr<sf::Text> mark;
    
    // functions
    void draw_board();
    void draw_mark(int, int, char);
    void process_mouse_click(int, int);    
};

#endif
