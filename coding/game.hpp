#pragma once

class Game {
private:
    bool mode;                      //Mode d'affichage : console, GUI
public:
    Game(bool mode = 0): mode(mode) {}               // Constructeur
    bool getMode();
    void gameTerminal(int iterationAmount)const;
    void gameGUI(int iterationAmount)const;
    void gameLoop();
};