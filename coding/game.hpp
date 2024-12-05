#pragma once
#include "grid.hpp"
#include<string>

class Game {
private:
    bool mode;                      //Mode d'affichage : console, GUI
    string outputFolder;
public:
    Game(bool mode = 0): mode(mode), outputFolder() {}               // Constructeur
    void getMode();
    Grid gameInit();
    void gameTerminal(int iterationAmount, std::string& outputFolder, Grid& grid)const;
    void gameGUI(Grid& grid)const;
    void gameLoop();
};