// Baron.cpp
#include "Baron.hpp"
#include <iostream>

Baron::Baron(std::string name) : Player(std::move(name),"Baron") {}

std::string Baron::specialAction(Player* target) {
    if (this->coins >= 3) {
        this->coins += 3;
        return "Baron paid 3 coins and got 6.";
    } else {
        return "Baron doesn't have enough coins.";
    }
}


void Baron::sanctioned() {
    Player::sanctioned(); 
    ++this->coins;
    std::cout << this->getName() << " was sanctioned and receives 1 coin as compensation (Baron ability)." << std::endl;
}
