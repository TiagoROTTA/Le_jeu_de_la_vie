#pragma once
#include "grid.hpp"
#include<string>

class Game {
private:
    bool mode;                      //Mode d'affichage : console, GUI
public:
    Game(bool mode = 0): mode(mode) {}               // Constructeur
    bool getMode();
    void gameTerminal(int iterationAmount, std::string& outputFolder, Grid& grid)const;
    void gameGUI(int iterationAmount, Grid& grid)const;
    void gameLoop();
};