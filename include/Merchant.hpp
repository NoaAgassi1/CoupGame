#pragma once
#include "player.hpp"

/**
 * @brief The Merchant role. Gains a bonus coin at the start of their turn
 * if they have 3 or more coins. Pays 2 coins to the pot when arrested.
 */
class Merchant : public Player {
protected:

    void startTurn() override;

    /**
     * @brief If arrested, lose 2 coins instead of 1.
     */
    void arrested() override;

public:
    /**
     * @brief Constructs a Merchant with the given name.
     * @param name The name of the player.
     */
    Merchant(std::string name) : Player(name, "Merchant") {}

   
};
