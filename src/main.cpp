#include <memory>
#include "game-manager.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<GameManager> gm(new GameManager());
    gm->start_game();
}
