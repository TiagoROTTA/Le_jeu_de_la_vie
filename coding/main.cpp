#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <fstream>


#include "game.hpp"

using namespace std;

//void gridInit(Grid& grid);

int main() {
    Game game;
    game.getMode();
    game.gameLoop();
    return 0;
}


/*
void gridInit(Grid &grid){
    cout << "Initialisation des etats de la grille"<< endl;
    cout << "Mettez 999 pour sortir du mode ou bien entrez la coordonnee selon  X puis en Y"<< endl;
    int posX;
    int posY;
    bool init = true;
    while(init){
        cout << "Entrez votre coordonnee selon Y: "<< endl;
        cin >> posY;
        if (posY == 999) init=!init;
        else if (posY<grid.getSizeY()){
            cout << "Entrez votre coordonnee selon X: "<< endl;
            cin >> posX;
            if (posX < grid.getSizeX()){
                cout<< "Etat de la cellule change"<< endl;
                grid.stateChange(posY, posX);
            }
            else{
                cout<<"Coordonnee hors du tableau"<< endl;
            }
        }
        else{
            cout << "Coordonnee hors du tableau"<< endl;
        }

    }
}*/