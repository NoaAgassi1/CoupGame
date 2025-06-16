#pragma once
#include "PlayersList.hpp"
#include <string>

/**
 * @class GameManager
 * @brief Singleton class that manages the overall flow of the Coup game.
 */
class GameManager {
private:
    static GameManager* instance;
    GameManager() = default;
    std::string lastResult;

public:
    /**
     * @brief Returns the singleton instance of the GameManager.
     * @return Reference to the GameManager instance.
     */
    static GameManager& getInstance();

    /**
     * @brief Frees the singleton instance.
     */
    static void free();

    /**
     * @brief Executes the gather action for the current player.
     */
    void gather();

    /**
     * @brief Executes the tax action for the current player.
     */
    void tax();

    /**
     * @brief Executes the bribe action for the current player.
     */
    void bribe();

    /**
     * @brief Attempts to arrest another player.
     * @param targetIdx Index of the player to arrest.
     */
    void arrest(size_t targetIdx);

    /**
     * @brief Performs a sanction on another player.
     * @param targetIdx Index of the player to sanction.
     */
    void sanction(size_t targetIdx);

    /**
     * @brief Performs a coup on another player.
     * @param targetIdx Index of the player to coup.
     */
    void coup(size_t targetIdx);

    /**
     * @brief Returns the name of the winner, if there is one.
     * @throws std::runtime_error if no winner yet.
     * @return The winner's name.
     */
    std::string winner();

    /**
     * @brief Returns the name of the current player.
     * @return The name of the player whose turn it is.
     */
    std::string turn() const;

    /**
     * @brief Returns the index of the current player.
     * @return Index in the player list.
     */
    size_t turnIdx() const;

    /**
     * @brief Returns a reference to a player by index.
     * @param idx The index of the player.
     * @return Reference to the Player.
     */
    Player& getPlayer(size_t idx);

    /**
     * @brief Returns the number of players still in the game.
     * @return The number of active players.
     */
    size_t playerCount() const;

    /**
     * @brief Returns a summary of all players.
     * @return A vector of strings representing each player.
     */
    std::vector<std::string> getPlayerSummaries() const;

    /**
     * @brief Performs the special action of the current player.
     * @param targetIndex Index of the target player, or -1 if not needed.
     * @return Message describing the result.
     */
    std::string specialAction(int targetIndex = -1);

    /**
     * @brief Returns the result of the last action taken.
     * @return A string describing the last action's outcome.
     */
    std::string getLastActionResult() const;

    /**
     * @brief Manually sets the result of the last action.
     * @param result Description of the result.
     */
    void setLastResult(const std::string& result);

    /**
     * @brief Advances the turn to the next player.
     */
    void advanceTurn();
};
