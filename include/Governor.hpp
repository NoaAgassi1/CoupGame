#pragma once
#include "player.hpp"

/**
 * @class Governor
 * @brief A special role that collects extra tax and can block tax actions.
 */
class Governor : public Player {
public:
    /**
     * @brief Constructs a Governor player with the given name.
     * @param name The name of the player.
     */
    explicit Governor(const std::string& name);

    /**
     * @brief Performs the Governor's tax action (collects 3 coins).
     * @return Message indicating the outcome.
     */
    std::string tax() override;

    /**
     * @brief Indicates that the Governor can block tax actions.
     * @return Always true.
     */
    bool blockTax() override { return true; }
};
