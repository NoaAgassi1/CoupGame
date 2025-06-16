#pragma once
#include "player.hpp"

/**
 * @class Baron
 * @brief A role with custom behavior for special actions and sanctions.
 */
class Baron : public Player {
private:
    /**
     * @brief Executes the Baron's special action.
     * @param target Pointer to the target player.
     * @return A string describing the result of the action.
     */
    std::string specialAction(Player* target) override;

    /**
     * @brief Handles the behavior when the Baron is sanctioned.
     */
    void sanctioned() override;

public:
    /**
     * @brief Constructs a Baron player with the given name.
     * @param name The name of the player.
     */
    explicit Baron(std::string name);
};
