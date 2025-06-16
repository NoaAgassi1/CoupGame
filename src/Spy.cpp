#include "Spy.hpp"

Spy::Spy(const std::string& name)
    : Player(name, "Spy") {}

std::string Spy::specialAction(Player* target) {
     if (!target) {
        return "No target selected.";
    }
    target->arrestBlocking(); 
    return " Spy " + this->getName() + " saw that " +
           target->getName() + " has " + std::to_string(coins) +
           " coins and blocked their arrest ability for the next turn.";}
