#include <iostream>
#include "game.hpp"
#include "grid.hpp"
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

bool Game::getMode(){
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "0 : Terminal" << endl;
    cout << "1 : Interface graphique" << endl;
    cin >> mode;
    return mode;
};

void Game::gameLoop(){
    if (!mode){
        int gridY = 20;
        int gridX = 40;
        Grid grid(gridY, gridX);

        grid.initGrid();
        while(true){
            grid.updateGrid();
            grid.displayGrid();
            this_thread::sleep_for(chrono::milliseconds(500));
            system("clear");
        }
    }
        
};