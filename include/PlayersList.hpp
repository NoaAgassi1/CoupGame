#pragma once
#include <vector>
#include <string>
#include <iterator>
#include "player.hpp"

/**
 * @class PlayersList
 * @brief Manages the list of players in the Coup game, including turn handling and singleton behavior.
 */
class PlayersList {
private:
    static PlayersList* instance;                       ///< Singleton instance
    std::vector<Player*> players;                       ///< List of all players
    std::vector<Player*>::iterator currentPlayerIt;     ///< Iterator for turn handling
    size_t turnCount = 0;                               ///< Counter for turn numbers

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    PlayersList() = default;

    // Disable copy and assignment
    PlayersList(const PlayersList&) = delete;
    PlayersList& operator=(const PlayersList&) = delete;

public:
    /**
     * @brief Destructor. Clears all players and frees memory.
     */
    ~PlayersList();

    /**
     * @brief Returns the singleton instance of the player list.
     * @return Reference to the singleton PlayersList instance.
     */
    static PlayersList& getInstance();

    /**
     * @brief Releases the singleton instance and its resources.
     */
    static void free();

    /**
     * @brief Clears all players from the game and resets internal state.
     */
    void clear();

    /**
     * @brief Initializes the game by creating players from a list of names.
     * @param names Vector of player names.
     */
    void init(const std::vector<std::string>& names);

    /**
     * @brief Creates a player with a random role and the given name.
     * @param name The name to assign to the player.
     * @return Pointer to the created Player object.
     */
    Player* createPlayer(std::string name);

    /**
     * @brief Adds a new player to the list.
     * @param player A pointer to a Player object.
     */
    void addPlayer(Player* player);

    /**
     * @brief Removes a player from the game.
     * @param player A pointer to the Player to remove.
     */
    void remove(Player* player);

    /**
     * @brief Initializes the turn iterator to the beginning of the player list.
     */
    void initTurns();

    /**
     * @brief Advances to the next player's turn, with logic for skipping or repeating turns.
     * @return A pointer to the next Player.
     */
    Player* getNext();

    /**
     * @brief Returns the player whose turn is currently active.
     * @return A pointer to the current Player.
     */
    Player* current() const;

    /**
     * @brief Returns the current turn number.
     * @return The number of turns that have occurred.
     */
    size_t getTurnNum() const;

    /**
     * @brief Searches for a player by name.
     * @param name The name of the player to find.
     * @return Pointer to the matching Player, or nullptr if not found.
     */
    Player* getPlayerByName(const std::string& name) const;

    /**
     * @brief Returns a pointer to the player at the specified index.
     * @param index Index in the player list.
     * @return Pointer to the Player at the given index.
     */
    Player* getPlayerByIndex(int index) const;

    /**
     * @brief Returns a const reference to the full list of players.
     * @return Const reference to the vector of Player pointers.
     */
    const std::vector<Player*>& getAllPlayers() const;

    /**
     * @brief Returns a dynamically allocated array of all player names.
     * @return Pointer to an array of strings containing player names (caller must delete[]).
     */
    std::string* getPlayerNames() const;

    /**
     * @class PlayersList::iterator
     * @brief Custom iterator class for iterating over the player list.
     */
    class iterator {
    private:
        std::vector<Player*>::iterator current; ///< Underlying STL iterator
    public:
        /**
         * @brief Constructs an iterator from a vector iterator.
         * @param current The underlying vector iterator.
         */
        iterator(std::vector<Player*>::iterator current);

        /**
         * @brief Dereference operator.
         * @return Reference to the Player object.
         */
        Player& operator*() const { return **current; }

        /**
         * @brief Arrow operator to access Player members.
         * @return Pointer to the Player object.
         */
        Player* operator->() const { return *current; }

        /**
         * @brief Prefix increment operator.
         * @return Reference to the updated iterator.
         */
        iterator& operator++();

        /**
         * @brief Postfix increment operator.
         * @return Copy of the iterator before increment.
         */
        const iterator operator++(int);

        /**
         * @brief Inequality comparison operator.
         * @param rhs Another iterator to compare with.
         * @return True if iterators are not equal.
         */
        bool operator!=(const iterator& rhs) const { return current != rhs.current; }
    };

    /**
     * @brief Returns an iterator to the beginning of the player list.
     */
    iterator begin() { return iterator(players.begin()); }

    /**
     * @brief Returns an iterator to the end of the player list.
     */
    iterator end() { return iterator(players.end()); }
};
