#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameManager.hpp"

/**
 * @class GUI
 * @brief Handles the graphical user interface for the Coup game using SFML.
 */
class GUI {
private:
    sf::RenderWindow window;         ///< Main SFML window
    GameManager& game;               ///< Reference to the game manager singleton

    // UI elements
    sf::Font font;                   ///< Font used for text rendering
    sf::Text title;                  ///< Title text displayed at the top
    sf::Text turnText;               ///< Shows whose turn it is
    sf::Text inputText;              ///< Shows the text input during registration
    sf::Text instructionsText;       ///< Instructions for player registration or gameplay
    sf::Text startHint;              ///< Hint to start the game after registration
    sf::Text statusText;             ///< Displays action feedback and status messages
    sf::RectangleShape inputBox;     ///< Box around the input text field
    std::vector<sf::Text> actionTexts;   ///< List of actions displayed to the player
    std::vector<sf::Text> playerTexts;   ///< Text labels showing current players
    sf::Text skipButton; ///< Button to skip turn if desired


    std::string currentInput;            ///< User's current input during registration
    std::vector<std::string> playerNames;///< Names of players being registered
    int selectedTargetIndex;            ///< Index of the selected target player (if any)

    bool isRegistering;                 ///< True if in registration phase

    /**
     * @brief Loads fonts and graphical resources.
     * @throws std::runtime_error if font loading fails.
     */
    void loadResources();

    /**
     * @brief Sets up the layout and positions of UI text elements.
     */
    void layoutText();

    /**
     * @brief Updates the main game screen during play mode.
     */
    void updateDisplay();

    /**
     * @brief Updates the registration screen display (entering player names).
     */
    void updateRegisterDisplay();

public:
    /**
     * @brief Constructs the GUI window and initializes layout.
     * @param game Reference to the GameManager singleton instance.
     */
    GUI(GameManager& game);

    /**
     * @brief Starts the GUI event loop and manages game display and input.
     */
    void run();
};
