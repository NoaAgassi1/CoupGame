#include "GUI.hpp"

int main() {
    GameManager& game = GameManager::getInstance();
    GUI gui(game);
    gui.run();
    GameManager::free();
    return 0;
}
