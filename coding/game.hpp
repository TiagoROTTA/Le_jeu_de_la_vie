#pragma once
#include "grid.hpp"
#include <string>

class Game {
private:
    bool mode;                                                      // Gamemode : terminal (0) or graphical interface (1)
    string outputFolder;                                            // Folder path where the grid will be written to in terminal mode

public:
    Game(bool mode = 0): mode(mode), outputFolder() {}              // Constructor
    void getMode();                                                 // Mode selection method
    Grid gameInit();                                                // Game start: setting up the first generation
    void gameTerminal(int iterationAmount, Grid& grid)const;        // Displaying the game in terminal
    void gameGUI(Grid& grid)const;                                  // Displaying the game with a graphical interface
    void gameLoop();                                                // Manage grid creation and the way the game is displayed according to user's choices
};