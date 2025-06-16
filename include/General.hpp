#pragma once
#include "player.hpp"

/**
 * @class General
 * @brief A role that can block coups and gains a coin when arrested.
 */
class General : public Player {
public:
    /**
     * @brief Constructs a General player with the given name.
     * @param name The name of the player.
     */
    explicit General(const std::string& name);

    /**
     * @brief Checks if the General is eligible to block a coup.
     * @return true if coup can be blocked (e.g., has at least 5 coins).
     */
    bool canBlockCoup() const;

    /**
     * @brief Blocks a coup attempt.
     * @return true if the coup was successfully blocked.
     */
    bool blockCoup() override;

    /**
     * @brief Called when the General is arrested. Gains 1 coin.
     */
    void arrested() override;
};
