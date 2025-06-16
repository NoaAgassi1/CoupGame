#include "Merchant.hpp"
#include "PlayersList.hpp"

void Merchant::startTurn() {
    if (this->getCoins() >= 3) {
        ++(*this);
        std::cout << "[AUTO] " << this->getName()
                  << " received a bonus coin (Merchant passive).\n";
    }
}

void Merchant::arrested() {
    if (this->getCoins() >= 2) {
        --(*this);
        --(*this);
    } else if (this->getCoins() == 1) {
        --(*this);
    }
    this->arrestedIndex = PlayersList::getInstance().getTurnNum();
}
