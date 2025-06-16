# Coup Game — C++ Project Implementation

This project is a full C++ implementation of the board game **Coup**, covering key aspects of the game's logic and extending it with additional rules, role abilities, turn management, action blocking, error handling, and a fully functional graphical interface using SFML.

The code is fully modular, class-based, well-documented, covered by unit tests, and properly handles memory management.

## 📌 Project Description

The project simulates the Coup game, focusing on the core mechanics while implementing several custom extensions to enhance gameplay and demonstrate advanced OOP concepts.

The system supports:

* Player registration and role assignment — with randomized, non-duplicate roles at game start.
* Core Coup mechanics — including resource gathering, tax, bribe, arrest, sanctions, and coup.
* Custom action-blocking system — allowing players to block certain actions even after they were performed, up until the target player's next turn.
* Special role-based abilities — each role provides unique interactions and gameplay dynamics.
* Automatic turn skipping — players with no legal moves can skip their turn using a "Skip Turn" option.
* Full error handling — any illegal action triggers a specific exception with a detailed message.
* Interactive GUI — built entirely with SFML, allowing dynamic player registration, interactive gameplay, and full game status visualization.
* Full unit testing and memory leak checks — ensuring correctness and reliability.

The project emphasizes advanced C++ design patterns, such as Singleton, inheritance, virtual functions, modular architecture, exception handling, and clean object-oriented structure.

## 🕹 Game Rules Implemented

* 2–6 players supported.

* At the start of the game, random roles are assigned (no duplicates).

* Available player actions:

* gather: Collect 1 coin (free).

* tax: Collect 2 coins (can be blocked by Governor).

* bribe: Pay 4 coins to receive an immediate extra turn.

* arrest: Steal 1 coin from another player (cannot target same player consecutively).

* sanction: Disable target's gather/tax for one round (costs 3 coins).

* coup: Eliminate a player (costs 7 coins, can be blocked in certain cases).

* specialAction: Unique abilities for Spy and Baron.

* Mandatory coup: if a player starts their turn with 10 or more coins, they must perform a coup.

* Sanctions automatically expire after a full round.

## 🎭 Roles and Abilities

* Governor: Collects 3 coins on tax; can block tax actions from others.
* Spy: Can block arrest on a selected player using specialAction.
* Baron: Invests 3 coins to receive 6 coins; loses only 1 coin if sanctioned.
* General: Can block coup (paying 5 coins); refunds 1 coin when arrested.
* Judge: Blocks bribe (opponent loses 4 coins); applies penalty to sanction initiators.
* Merchant: Gains 1 extra coin at turn start if holding 3+ coins; pays 2 coins to the bank instead of losing coins on arrest.

## 🔄 Turn & Blocking Logic

* Sanctions disable gather/tax for one turn.
* Bribe grants an immediate extra turn.
* Blocking is allowed even after actions are performed, until the target player's next turn.
* If no legal moves are available, the player may skip their turn using the Skip Turn button in the GUI.

## 🖥 Project Structure

* src/: C++ source files
* include/: C++ header files
* assets/: Fonts and other GUI resources
* tests/: Unit tests using doctest
* Makefile: Build automation
* README.md: Project documentation

## 💻 Technologies Used

* C++17
* SFML 2.5 (GUI)
* doctest (unit testing)
* Valgrind (memory leak detection)
* POSIX Makefile

## 🚀 Build and Run Instructions

### Install SFML (Ubuntu):

sudo apt update
sudo apt install libsfml-dev

### Build and run the project:

make Main
./coup\_gui

### Clean build files:

make clean

## 🧪 Unit Tests

### Build tests:

make test

### Run tests:

./tests

## 🔎 Memory Leak Checks

make valgrind

## 🧩 Main Classes

* Player (abstract base class)
* Governor, Spy, General, Baron, Judge, Merchant (role-specific subclasses)
* PlayersList (singleton managing all players)
* GameManager (singleton managing game state)
* GUI (SFML-based interface)

## 📝 Code Details

* The codebase is fully documented using Doxygen-style comments.
* Unit tests cover all key game logic, actions, edge cases, and special abilities.
* Invalid actions throw specific exceptions.
* Memory management verified using Valgrind — no leaks detected.
* Full separation between game logic and GUI layers.

## ⚠️ Academic Integrity Notice

During development, I used ChatGPT strictly for explanations, documentation generation, and structural design suggestions.
All code was fully written and implemented independently.

## 👩‍💻 Author

Noa Agassi
Computer Science & Cyber — Ariel University — 2025

