#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>


#include "game.hpp"

int main() {
    Game game;
    game.getMode();
    game.gameLoop();
    return 0;
}
