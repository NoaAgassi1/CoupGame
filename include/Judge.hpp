#pragma once
#include "player.hpp"

/**
 * @brief Represents the Judge role, which can block bribe actions and punishes attackers who sanction him.
 */
class Judge : public Player {
private:
    bool wantsToBlockBribe = false; ///< Whether the judge chose to block a bribe.

public:
    /**
     * @brief Constructs a Judge with a given name.
     * @param name The player's name.
     */
    explicit Judge(const std::string& name);

    /**
     * @brief Sets whether the judge wants to block a bribe action.
     * @param decision True if blocking, false otherwise.
     */
    void setBlockDecision(bool decision);

    /**
     * @brief Overrides the blockBribe method to return the judge's decision.
     * @return True if the bribe is blocked.
     */
    bool blockBribe() override;

};
