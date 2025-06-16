#pragma once
#include <string>
#include <iostream>
using namespace std;

/**
 * @class Player
 * @brief Abstract base class representing a player in the Coup game.
 *        Provides default behavior for actions, which can be overridden by roles.
 */
class Player {
private:
    std::string name;           ///< Player's name
    std::string roleName;       ///< The role name (e.g., Governor, Spy, etc.)
    bool isSanctioned;          ///< True if the player is under sanction
    bool isBribe;               ///< True if the player used bribe last turn

protected:
    size_t arrestedIndex;       ///< The turn number the player was last arrested
    size_t coins;               ///< Number of coins the player has
    bool blockArrest;           ///< True if the player is blocked from arresting

    /**
     * @brief Initializes a new Player object with name and role.
     * @param name The name of the player.
     * @param roleName The role assigned to the player.
     */
    Player(std::string name, std::string roleName)
        : name(name),
          roleName(roleName),
          isSanctioned(false),
          isBribe(false),
          arrestedIndex(0),
          coins(0),
          blockArrest(false) {}

    /**
     * @brief Role-specific method that blocks tax (default: false).
     * @return true if the role can block tax, false otherwise.
     */
    virtual bool blockTax() { return false; }

    /**
     * @brief Role-specific method that blocks coup (default: false).
     * @return true if the role can block coup, false otherwise.
     */
    virtual bool blockCoup() { return false; }

    /**
     * @brief Role-specific method that blocks bribe (default: false).
     * @return true if the role can block bribe, false otherwise.
     */
    virtual bool blockBribe() { return false; }

    /**
     * @brief Called when the player is arrested (reduces coins, tracks turn).
     */
    virtual void arrested();

    /**
     * @brief Puts the player under sanction (prevents gather/tax).
     */
    virtual void sanctioned();

public:
    /**
     * @brief Virtual destructor to support polymorphic cleanup.
     */
    virtual ~Player() = default;

    /**
     * @brief Performs the tax action (adds coins if not blocked).
     * @return Message indicating success or failure.
     */
    virtual std::string tax();

    /**
     * @brief Indicates whether the role can perform tax.
     * @return true if tax is allowed, false otherwise.
     */
    virtual bool canTax() const { return true; }

    /**
     * @brief Executes the special action of the role (if any).
     * @param target Optional target player for the action.
     * @return Message describing the result of the action.
     */
    virtual std::string specialAction(Player* target = nullptr);

    /**
     * @brief Returns the player's name.
     * @return The name of the player.
     */
    std::string getName() const;

    /**
     * @brief Returns the player's role.
     * @return The role name of the player.
     */
    std::string role() const;

    /**
     * @brief Called at the start of the player's turn (can be overridden).
     */
    virtual void startTurn();

    /**
     * @brief Returns how many coins the player has.
     * @return The number of coins.
     */
    size_t getCoins() const;

    /**
     * @brief Checks if the player used bribe last turn.
     * @return true if bribed, false otherwise.
     */
    bool getIsBribe() const;

    /**
     * @brief Resets the bribe status to false.
     */
    void unbribe();

    /**
     * @brief Blocks this player from arresting in the next turn.
     */
    void arrestBlocking();

    /**
     * @brief Resets the arrest blocking flag.
     */
    void arrestBlockingReset();

    /**
     * @brief Performs the gather action (gain 1 coin, unless sanctioned).
     * @return Message indicating result of gather action.
     */
    std::string gather();

    /**
     * @brief Performs the bribe action (pay 4 coins, can be blocked).
     * @return Message indicating result of bribe.
     */
    virtual std::string bribe();

    /**
     * @brief Sets the bribe status of the player.
     * @param value true if player has bribed this turn, false otherwise.
     */
    void setBribe(bool value) { isBribe = value; }

    /**
     * @brief Attempts to arrest another player (can be blocked).
     * @param target The player to be arrested.
     * @return Message describing the outcome.
     */
    std::string arrest(Player* target);

    /**
     * @brief Performs a sanction on another player (costs 3 coins).
     * @param target The player to sanction.
     * @return Message describing the result.
     */
    std::string sanction(Player* target);

    /**
     * @brief Performs a coup on another player (costs 7 coins).
     * @param target The player to coup.
     * @return Message describing the result.
     */
    std::string coup(Player* target);

    /**
     * @brief Increments the player's coin count by 1.
     * @return Reference to the current player.
     */
    Player& operator++();

    /**
     * @brief Increments the player's coins by a given amount.
     * @param amount Number of coins to add.
     * @return Reference to the current player.
     */
    Player& operator+=(int amount);

    /**
     * @brief Decrements the player's coin count (if > 0).
     * @return Reference to the current player.
     */
    Player& operator--();

    /**
     * @brief Checks if the player is under sanction.
     * @return true if sanctioned, false otherwise.
     */
    bool getIsSanctioned() const;

    /**
     * @brief Removes the sanction status from the player.
     */
    void clearSanction();
};
