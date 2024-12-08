#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>

#include "game.hpp"

int main() {
    Game game;              // Creating a new game instance
    game.getMode();         // Gamemode selection: terminal (0) or graphical interface (1)
    game.gameLoop();        // Manage grid creation and the way the game is displayed according to user's choices and Conway's game of life rules
    return 0;
}