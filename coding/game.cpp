#include <iostream>
#include "game.hpp"
#include "grid.hpp"
#include <chrono>
#include <thread>
#include <fstream>
#include <string>

using namespace std;

bool Game::getMode(){
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "0 : Terminal" << endl;
    cout << "1 : Interface graphique" << endl;
    cin >> mode;
    return mode;
};

void Game::gameTerminal(int iterationAmount)const{
    int gridY = 20;
    int gridX = 40;
    Grid grid(gridY, gridX);
    string outputFolder= grid.initGrid();
    for (int i = 0; i<iterationAmount; i++) {
        string filePath = outputFolder + "/iteration_" + to_string(i) + ".txt";
        grid.changePath(filePath);
        grid.updateGrid();
        grid.displayGrid();
        this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
    }
};

void Game::gameGUI(int iterationAmount) const{

}


void Game::gameLoop(){
    int iterationAmount;
    cout << "Entrez le nombre d'itérations souhaité : " << endl;
    cin >> iterationAmount;
    if (!mode){
        gameTerminal(iterationAmount);
    }
    else {
        gameGUI(iterationAmount);
    }
};