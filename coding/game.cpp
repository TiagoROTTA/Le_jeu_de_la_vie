#include <iostream>
#include "game.hpp"
#include "grid.hpp"
#include <chrono>
#include <thread>

using namespace std;

bool Game::getMode(){
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "0 : Terminal" << endl;
    cout << "1 : Interface graphique" << endl;
    cin >> mode;
    return mode;
};

void Game::gameLoop(bool mode){
    int gridY = 20;
    int gridX = 40;
    int test;
    Grid grid(gridY, gridX);

    grid.initGrid();
    grid.displayGrid();
    cin >> test;
    while(true){
        grid.updateGrid();
        grid.displayGrid();
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
    }
};