#include <iostream>
#include "game.hpp"
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "GUI.hpp"

using namespace std;

bool Game::getMode(){
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "0 : Terminal" << endl;
    cout << "1 : Interface graphique" << endl;
    cin >> mode;
    return mode;
};

void Game::gameTerminal(int iterationAmount, string& outputFolder, Grid& grid)const{
    for (int i = 0; i<iterationAmount; i++) {
        string filePath = outputFolder + "/iteration_" + to_string(i) + ".txt";
        grid.changePath(filePath);
        grid.updateGrid();
        grid.displayGrid();
        this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
    }
};

void Game::gameGUI(int iterationAmount, Grid& grid) const{
    GUI graphic(5, 100, 100, &grid);
    graphic.play();

}


void Game::gameLoop(){
    int iterationAmount;
    cout << "Entrez le nombre d'itérations souhaité : " << endl;
    cin >> iterationAmount;
    int gridY = 20;
    int gridX = 40;
    Grid grid(gridY, gridX);
    string outputFolder= grid.initGrid();
    if (!mode){
        gameTerminal(iterationAmount, outputFolder, grid);
    }
    else {
        gameGUI(iterationAmount, grid);
    }
};