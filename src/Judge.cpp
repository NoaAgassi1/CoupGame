#include "Judge.hpp"
#include "PlayersList.hpp"

Judge::Judge(const std::string& name)
    : Player(name, "Judge") {}

void Judge::setBlockDecision(bool decision) {
    wantsToBlockBribe = decision;
}

bool Judge::blockBribe() {
    return wantsToBlockBribe;
}



