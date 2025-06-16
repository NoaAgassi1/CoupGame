#include "GUI.hpp"
#include <iostream>

GUI::GUI(GameManager& game)
    : window(sf::VideoMode(800, 600), "Coup GUI"), game(game), selectedTargetIndex(-1), isRegistering(true) {
    loadResources();
    layoutText();

    inputBox.setSize(sf::Vector2f(300, 30));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(250, 150);

    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(255, 152);

    instructionsText.setFont(font);
    instructionsText.setCharacterSize(20);
    instructionsText.setFillColor(sf::Color::Black);
    instructionsText.setString("Enter player names (2-6). Press Enter after each:");
    instructionsText.setPosition(60, 100);

    startHint.setFont(font);
    startHint.setCharacterSize(18);
    startHint.setFillColor(sf::Color::Green);
    startHint.setString("Press Enter again to start if you entered at least 2 names");
    startHint.setPosition(120, 400);

    statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::Blue);
    statusText.setPosition(150, 350);

    skipButton.setFont(font);
    skipButton.setCharacterSize(20);
    skipButton.setFillColor(sf::Color::Red);
    skipButton.setString("Skip Turn");
    skipButton.setPosition(600, 550); 

}

void GUI::loadResources() {
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    title.setFont(font);
    title.setString("Coup Game");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::Black);
    title.setPosition(250, 20);

    turnText.setFont(font);
    turnText.setCharacterSize(24);
    turnText.setFillColor(sf::Color::Blue);
    turnText.setPosition(50, 70);
}

void GUI::layoutText() {
    static const std::vector<std::string> actions = {
        "- Gather", "- Tax", "- Bribe", "- Arrest (select player)",
        "- Sanction (select player)", "- Coup (select player)", "- Special Action (only for Baron and Spy)"
    };

    actionTexts.clear();
    for (size_t i = 0; i < actions.size(); ++i) {
        sf::Text action;
        action.setFont(font);
        action.setCharacterSize(20);
        action.setFillColor(sf::Color::Black);
        action.setString(actions[i]);
        action.setPosition(220, 120 + i * 30); 
        actionTexts.push_back(action);
    }
}

void GUI::updateDisplay() {
    window.clear(sf::Color(200, 200, 200)); 
    window.draw(title);

    turnText.setString("Current Turn: " + game.turn());
    window.draw(turnText);

    for (size_t i = 0; i < actionTexts.size(); ++i) {
        actionTexts[i].setPosition(60, 120 + i * 30); 
        window.draw(actionTexts[i]);
    }

    playerTexts.clear();
    const auto& players = game.getPlayerSummaries();
    for (size_t i = 0; i < players.size(); ++i) {
        sf::Text pText;
        pText.setFont(font);
        pText.setCharacterSize(18);
        pText.setFillColor((int)i == selectedTargetIndex ? sf::Color::Red : sf::Color::Black);
        pText.setString(players[i]);
        pText.setPosition(500, 120 + i * 25); 
        playerTexts.push_back(pText);
        window.draw(playerTexts.back());
    }

    statusText.setString(game.getLastActionResult());
    statusText.setPosition(60, 520); 
    window.draw(statusText);
    window.draw(skipButton);

    window.display();
}


void GUI::updateRegisterDisplay() {
    window.clear(sf::Color(200, 200, 200));
    window.draw(title);
    window.draw(instructionsText);
    window.draw(inputBox);

    inputText.setString(currentInput);
    window.draw(inputText);

    sf::Text playerList;
    playerList.setFont(font);
    playerList.setCharacterSize(18);
    playerList.setFillColor(sf::Color::Blue);

    std::string names;
    for (const std::string& name : playerNames)
        names += name + "\n";

    playerList.setString(names);
    playerList.setPosition(100, 200);
    window.draw(playerList);

    statusText.setString(game.getLastActionResult());
    window.draw(statusText);

    if (playerNames.size() >= 2)
        window.draw(startHint);

    window.display();
}

void GUI::run() {
    srand(time(nullptr));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (isRegistering) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8) {
                        if (!currentInput.empty())
                            currentInput.pop_back();
                    } else if (event.text.unicode == 13 || event.text.unicode == 10) {
                        if (!currentInput.empty()) {
                            bool duplicate = false;
                            for (const std::string& existing : playerNames) {
                                if (existing == currentInput) {
                                    duplicate = true;
                                    break;
                                }
                            }
                            if (!duplicate) {
                                playerNames.push_back(currentInput);
                                game.setLastResult("");
                            } else {
                                game.setLastResult("[ERROR] Duplicate name: " + currentInput);
                            }
                            currentInput.clear();
                        } else if (playerNames.size() >= 2 && playerNames.size() <= 6) {
                            PlayersList::getInstance().init(playerNames);
                            isRegistering = false;
                            game.setLastResult("");
                        }
                    } else if (event.text.unicode < 128) {
                        currentInput += static_cast<char>(event.text.unicode);
                    }
                }
            } else {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                        if (skipButton.getGlobalBounds().contains(mousePos)) {
                            game.advanceTurn();
                            statusText.setString("Turn skipped.");
                            continue; 
                        }

                        for (size_t i = 0; i < playerTexts.size(); ++i) {
                            if (playerTexts[i].getGlobalBounds().contains(mousePos)) {
                                selectedTargetIndex = static_cast<int>(i);
                                break;
                            }
                        }

                        for (size_t i = 0; i < actionTexts.size(); ++i) {
                            if (actionTexts[i].getGlobalBounds().contains(mousePos)) {
                                switch (i + 1) {
                                    case 1: game.gather(); break;
                                    case 2: game.tax(); break;
                                    case 3: game.bribe(); break;
                                    case 4:
                                        if (selectedTargetIndex != -1)
                                            game.arrest(selectedTargetIndex);
                                        break;
                                    case 5:
                                        if (selectedTargetIndex != -1)
                                            game.sanction(selectedTargetIndex);
                                        break;
                                    case 6:
                                        if (selectedTargetIndex != -1)
                                            game.coup(selectedTargetIndex);
                                        break;
                                    case 7:
                                        game.specialAction(selectedTargetIndex);
                                        break;
                                    default: break;
                                }
                                break;
                            }
                        }
                    }
                }

                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Num1: game.gather(); break;
                        case sf::Keyboard::Num2: game.tax(); break;
                        case sf::Keyboard::Num3: game.bribe(); break;
                        case sf::Keyboard::Num4:
                            if (selectedTargetIndex != -1)
                                game.arrest(selectedTargetIndex);
                            break;
                        case sf::Keyboard::Num5:
                            if (selectedTargetIndex != -1)
                                game.sanction(selectedTargetIndex);
                            break;
                        case sf::Keyboard::Num6:
                            if (selectedTargetIndex != -1)
                                game.coup(selectedTargetIndex);
                            break;
                        case sf::Keyboard::Num7: game.specialAction(); break;
                        default: break;
                    }
                }
            }
        }

        // עדכון GUI
        if (isRegistering) {
            updateRegisterDisplay();
        } else {
            updateDisplay();
        }

        if (!isRegistering && game.playerCount() == 1) {
            std::string winner = game.winner();
            std::cout << "\n------[GAME OVER]------\n The winner is: " << winner << "!!\n";
            window.close();
        }

    }
}

