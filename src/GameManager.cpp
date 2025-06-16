#include "GameManager.hpp"
#include "Governor.hpp"

GameManager* GameManager::instance = nullptr;

GameManager& GameManager::getInstance() {
    if (!instance) instance = new GameManager();
    return *instance;
}

void GameManager::free() {
    delete instance;
    instance = nullptr;
}

void GameManager::gather() {
    lastResult = PlayersList::getInstance().current()->gather();
    std::cout << lastResult << std::endl;
    if (lastResult.find("[SUCCESS]") != std::string::npos) {
        GameManager::getInstance().advanceTurn();

    }
}

void GameManager::tax() {
    Player* current = PlayersList::getInstance().current();


    if (!current->canTax()) {
        lastResult = current->getName() + " cannot perform tax.";
        std::cout << lastResult << std::endl;
        return;
    }

    for (Player* p : PlayersList::getInstance().getAllPlayers()) {
        if (p != current) {
            Governor* gov = dynamic_cast<Governor*>(p); 
            if (gov) {
                std::string answer;
                std::cout << gov->getName() << " (Governor), do you want to block "
                        << current->getName() << "'s tax? (y/n): ";
                std::cin >> answer;

                if (answer == "y") {
                    lastResult = gov->getName() + " blocked your tax.";
                    std::cout << lastResult << std::endl;
                    return;
                }
            }
        }
    }

    lastResult = current->tax();
    std::cout << lastResult << std::endl;

    if (lastResult.find("[SUCCESS]") != std::string::npos) {
        GameManager::getInstance().advanceTurn();
    }
}


void GameManager::bribe() {
    Player* current = PlayersList::getInstance().current();

    std::string result = current->bribe();  

    if (result.find("can't") != std::string::npos || result.find("need") != std::string::npos) {
        lastResult = result;
        return;
    }

    for (Player* p : PlayersList::getInstance().getAllPlayers()) {
        if (p != current && p->role() == "Judge") {
            std::string answer;
            std::cout << p->getName() << " (Judge), do you want to block "
                      << current->getName() << "'s bribe? (y/n): ";
            std::cin >> answer;

            if (answer == "y") {
                lastResult = p->getName() + " blocked your bribe. You lost 4 coins.";
                PlayersList::getInstance().getNext();  
                return;
            }
        }
    }

    current->setBribe(true);
    lastResult = "[SUCCESS] Bribe successful. You may perform an extra action.";
}


void GameManager::arrest(size_t idx) {
    Player* target = PlayersList::getInstance().getAllPlayers().at(idx);
    lastResult = PlayersList::getInstance().current()->arrest(target);
    std::cout << lastResult << std::endl;
    if (lastResult.find("[SUCCESS]") != std::string::npos) {
        GameManager::getInstance().advanceTurn();
    }
}

void GameManager::sanction(size_t idx) {
    Player* target = PlayersList::getInstance().getAllPlayers().at(idx);
    lastResult = PlayersList::getInstance().current()->sanction(target);
    std::cout << lastResult << std::endl;
    if (lastResult.find("[SUCCESS]") != std::string::npos) {
        GameManager::getInstance().advanceTurn();

    }
}

void GameManager::coup(size_t idx) {
    Player* target = PlayersList::getInstance().getAllPlayers().at(idx);
    lastResult = PlayersList::getInstance().current()->coup(target);
    std::cout << lastResult << std::endl;
    if (lastResult.find("[SUCCESS]") != std::string::npos) {
        GameManager::getInstance().advanceTurn();

    }
}

std::string GameManager::specialAction(int targetIndex) {
    Player* current = PlayersList::getInstance().current();
    if (!current) return "No current player.";

    
    if (targetIndex != -1) {
        Player* target = PlayersList::getInstance().getPlayerByIndex(targetIndex);
        lastResult = current->specialAction(target);
    } else {
        lastResult = current->specialAction();
    }

    std::cout << lastResult << std::endl;
    if (lastResult.find("[SUCCESS]") != std::string::npos) {
        GameManager::getInstance().advanceTurn();

    }

    return lastResult;
}

std::string GameManager::turn() const {
    return PlayersList::getInstance().current()->getName();
}

size_t GameManager::turnIdx() const {
    const auto& list = PlayersList::getInstance().getAllPlayers();
    Player* current = PlayersList::getInstance().current();
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i] == current) return i;
    }
    return 0; // fallback
}

Player& GameManager::getPlayer(size_t idx) {
    return *PlayersList::getInstance().getAllPlayers().at(idx);
}

size_t GameManager::playerCount() const {
    return PlayersList::getInstance().getAllPlayers().size();
}

std::string GameManager::winner() {
    const auto& list = PlayersList::getInstance().getAllPlayers();
    if (list.size() == 1) return list.front()->getName();
    throw std::runtime_error("No winner yet");
}

std::vector<std::string> GameManager::getPlayerSummaries() const {
    std::vector<std::string> summaries;
    const auto& players = PlayersList::getInstance().getAllPlayers();

    for (const Player* p : players) {
        std::string summary = p->getName() + " (" + p->role() + ") - ";

        if (p == PlayersList::getInstance().current()) {
            summary += std::to_string(p->getCoins()) + " coins";
        } else {
            summary += "?? coins";
        }

        if (p->getIsSanctioned()) summary += " [Sanction]";
        if (p->getIsBribe()) summary += " [Bribe]";

        summaries.push_back(summary);
    }

    return summaries;
}
std::string GameManager::getLastActionResult() const {
    return lastResult;
}
void GameManager::setLastResult(const std::string& result) {
    lastResult = result;
}


void GameManager::advanceTurn() {
    Player* next = PlayersList::getInstance().getNext();
    if (next) {
        next->startTurn();  
    }
}
