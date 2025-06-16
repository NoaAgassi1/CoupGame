#include "General.hpp"

General::General(const std::string& name)
    : Player(name, "General") {}

bool General::canBlockCoup() const {
    return this->getCoins() >= 5;
}

bool General::blockCoup() {
    if (!canBlockCoup()) return false;

    for (int i = 0; i < 5; ++i) --(*this); 
    return true;
}

void General::arrested() {
    ++(*this); 
}
