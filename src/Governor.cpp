#include "Governor.hpp"

Governor::Governor(const std::string& name)
    : Player(name, "Governor") {}

std::string Governor::tax() {
    if (getIsSanctioned()) {
        return "You are sanctioned and cannot perform tax.";
    }

    this->coins += 3;
    return "[SUCCESS] " + this->getName() + " took 3 coins using enhanced tax (Governor ability).";
}



