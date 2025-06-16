#include "PlayersList.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include "Governor.hpp"
#include "Spy.hpp"
#include "General.hpp"
#include "Merchant.hpp"
#include "Judge.hpp"
#include "Baron.hpp"

PlayersList* PlayersList::instance = nullptr;

PlayersList::~PlayersList() {
    clear();
}

PlayersList& PlayersList::getInstance() {
    if (!instance) {
        instance = new PlayersList();
    }
    return *instance;
}

void PlayersList::free() {
    delete instance;
    instance = nullptr;
}

void PlayersList::clear() {
    for (Player* p : players) {
        delete p;
    }
    players.clear();
    turnCount = 0;
    currentPlayerIt = players.end();
}

void PlayersList::init(const std::vector<std::string>& names) {
    clear();

    if (names.size() < 2 || names.size() > 6) {
        throw std::invalid_argument("Number of players must be between 2 and 6.");
    }

    for (const std::string& name : names) {
        if (getPlayerByName(name)) {
            throw std::invalid_argument("Duplicate player name: " + name);
        }

        Player* newPlayer = createPlayer(name);
        players.push_back(newPlayer);
    }

    currentPlayerIt = players.begin();
}


Player* PlayersList::createPlayer(std::string name) {
    switch (rand() % 6) {
        case 0: return new Governor(name);
        case 1: return new Spy(name);
        case 2: return new General(name);
        case 3: return new Merchant(name);
        case 4: return new Judge(name);
        case 5: return new Baron(name);
        default: return new Governor(name);
    }
}


void PlayersList::addPlayer(Player* player) {
    if (player) players.push_back(player);
}

void PlayersList::remove(Player* player) {
    auto it = std::find(players.begin(), players.end(), player);
    if (it != players.end()) {
        bool wasCurrent = (it == currentPlayerIt);
        delete *it;
        players.erase(it);

        if (players.empty()) {
            currentPlayerIt = players.end();
        } else if (wasCurrent) {
            currentPlayerIt = players.begin();
        }
       
    }
}

void PlayersList::initTurns() {
    currentPlayerIt = players.begin();
    turnCount = 0;
}

Player* PlayersList::getNext() {
    if (players.empty()) return nullptr;

    Player* prev = nullptr;
    if (currentPlayerIt != players.end()) {
        prev = *currentPlayerIt;
    }

    if (prev && prev->getIsBribe()) {
        prev->unbribe(); 
        std::cout << prev->getName() << " bribed last turn and gets an extra turn!" << std::endl;

        ++turnCount;
        return prev;
    }
    if (currentPlayerIt == players.end() || ++currentPlayerIt == players.end()) {
        currentPlayerIt = players.begin();
    }

    Player* next = *currentPlayerIt;

    if (prev) {
        if (prev->getIsSanctioned()) {
            prev->clearSanction();
        }
        prev->arrestBlockingReset();
    }

    ++turnCount;

    return next;
}



Player* PlayersList::getPlayerByIndex(int index) const {
    const auto& all = getAllPlayers();  
    if (index >= 0 && index < (int)all.size()) {
        return all[index];
    }
    return nullptr;
}



Player* PlayersList::current() const {
    if (players.empty() || currentPlayerIt == players.end()) return nullptr;
    return *currentPlayerIt;
}

size_t PlayersList::getTurnNum() const {
    return turnCount;
}

Player* PlayersList::getPlayerByName(const std::string& name) const {
    for (Player* p : players) {
        if (p->getName() == name) return p;
    }
    return nullptr;
}

const std::vector<Player*>& PlayersList::getAllPlayers() const {
    return players;
}

std::string* PlayersList::getPlayerNames() const {
    std::string* names = new std::string[players.size()];
    for (size_t i = 0; i < players.size(); ++i) {
        names[i] = players[i]->getName();
    }
    return names;
}

PlayersList::iterator& PlayersList::iterator::operator++() {
    auto next = ++current;
    if (next != PlayersList::getInstance().players.end() &&
        *next == PlayersList::getInstance().current()) {
        ++current;
    }
    return *this;
}

const PlayersList::iterator PlayersList::iterator::operator++(int) {
    iterator tmp = *this;
    ++*this;
    return tmp;
}

PlayersList::iterator::iterator(std::vector<Player*>::iterator current)
    : current(current) {
    if (this->current == PlayersList::getInstance().players.begin() &&
        *this->current == PlayersList::getInstance().current()) {
        ++this->current;
    }
}
