//agassinoa02@gmail.com
#include "player.hpp"
#include "PlayersList.hpp" 
#include "General.hpp"

using namespace std;

string Player::getName() const { return name;}

string Player::role() const { return roleName;}

size_t Player::getCoins() const {
    return coins;
}

bool Player::getIsBribe() const {return isBribe;}

void Player::unbribe() {isBribe = false;}


void Player::arrestBlocking() {
    std::cout << "[DEBUG] " << this->getName() << " was blocked by Spy." << std::endl;
    blockArrest = true;
}

void Player::arrestBlockingReset() {this->blockArrest = false;}



std::string Player::gather() {
    if (isSanctioned) {
        return "[FAILURE] " + this->getName() + " is sanctioned and cannot gather coins this turn.";

    }
    ++(*this);
    return "[SUCCESS] "+ this->getName()+" gathered 1 coin.";
}

std::string Player::bribe() {
    if (isBribe) {
        return "You can't bribe two turns in a row.";}
    if (coins < 4) {
        return "You need at least 4 coins to bribe.";}

    coins -= 4;
    isBribe = true;
    return "[PENDING] Paid 4 coins for bribe.";  
}


void Player::arrested() {
    if (this->role() != "General") {
        --(*this); // Lose 1 coin
    }
    arrestedIndex = PlayersList::getInstance().getTurnNum();
}


std::string Player::arrest(Player* target) {
    if (this->blockArrest) {return this->getName() + " can't arrest because you're blocked by a spy.";}
    
    if (this == target) { return "You cannot arrest yourself.";}

    if (!target) { return "Invalid arrest target.";}

    size_t lastTurn = target->arrestedIndex;
    size_t currentTurn = PlayersList::getInstance().getTurnNum();
    if (lastTurn > 0 && currentTurn - lastTurn == 1) {
        return target->getName() + " was just arrested last turn.";
    }

    if (target->getCoins() == 0 && target->role() != "General") {
        return target->getName() + " has no coins to be arrested.";}

    target->arrested();

    std::string result = "[SUCCESS] " + this->getName() + " arrested " + target->getName() + ".\n";

    if (target->role() == "General") {
        result += target->getName() + " (General) lost 0 coins.\n";
        ++(*this);  // מקבל מטבע כרגיל
        result += this->getName() + " gained 1 coin.";
    }
    else if (target->role() == "Merchant") {
        result += target->getName() + " (Merchant) lost 2 coins.\n";
        result += this->getName() + " gained 0 coins.";
    }
    else {
        result += target->getName() + " lost 1 coin.\n";
        ++(*this);
        result += this->getName() + " gained 1 coin.";
    }
    return result;
}



std::string Player::sanction(Player* target) {
    if (!target) {
        return "No target selected for sanction.";
    }
    if (target == this) {
        return "You cannot sanction yourself.";
    }
    if (target->isSanctioned) {
        return target->getName() + " is already under sanction.";
    }
    if (coins < 3) {
        return "Not enough coins to perform sanction (requires 3).";
    }

    coins -= 3;
    target->sanctioned();

    std::string message = "[SUCCESS] Sanctioned " + target->getName() + ".";

    if (target->role() == "Judge") {
        if (coins >= 1) {
            coins -= 1;
            message += " Target is a Judge - you paid an extra coin.";
        } else {
            message += " Target is a Judge - you were supposed to pay an extra coin, but you had no coins.";
        }
    }

    return message;
}


std::string Player::coup(Player* target) {
    if (!target) {
        return "No target selected for coup.";
    }
    if (coins < 7) {
        return "Not enough coins to perform a coup.";
    }

    std::string targetName = target->getName();
    coins -= 7; 

    for (Player* p : PlayersList::getInstance().getAllPlayers()) {
        if (p->role() == "General") {
            General* general = dynamic_cast<General*>(p);
            if (general && general->canBlockCoup()) {
                std::string answer;
                std::cout << "[QUESTION] " << general->getName()
                          << ": Do you want to block the coup against "
                          << targetName << "? (y/n): ";
                std::cin >> answer;

                if (answer == "y" || answer == "Y") {
                    general->blockCoup(); 
                    return "[SUCCESS] Coup was blocked by " + general->getName() + ". You still lost 7 coins.";
                }
            }
        }
    }

    PlayersList::getInstance().remove(target);

    return "[SUCCESS] Coup succeeded against " + targetName + ".";
}



Player& Player::operator++() {
    ++coins;
    return *this;
}

Player& Player::operator--() {
    if (coins > 0) --coins;
    return *this;
}

Player& Player::operator+=(int amount) {
    coins += amount;
    return *this;
}



std::string Player::tax() {
    if (isSanctioned) {
    return "[FAILURE] You are sanctioned and cannot perform tax.";
}
    coins += 2;
    return "[SUCCESS] You received 2 coins from tax.";
}


void Player::sanctioned() {isSanctioned = true;}

std::string Player::specialAction(Player* target) {
    return "This role has no special action.";
}

void Player::startTurn() {
}


bool Player::getIsSanctioned() const {
    return isSanctioned;
}

void Player::clearSanction() {
    isSanctioned = false;
}


