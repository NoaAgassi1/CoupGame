#pragma once
#include "player.hpp"

/**
 * @brief Spy role – can block another player from performing arrest during this turn.
 */
class Spy : public Player {
public:
    /**
     * @brief Constructs a Spy player.
     * @param name The name of the player.
     */
    Spy(const std::string& name);

    /**
     * @brief Spy's unique action – blocks a target from arresting this turn.
     * @return A message describing the result.
     */
    std::string specialAction(Player* target) override;
};