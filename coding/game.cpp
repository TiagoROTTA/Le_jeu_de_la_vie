#include <iostream>
#include "game.hpp"
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "GUI.hpp"

using namespace std;

void Game::getMode(){
    cout << "Choisissez le mode d'affichage :" << endl;
    cout << "0 : Terminal" << endl;
    cout << "1 : Interface graphique" << endl;
    cin >> mode;
};
Grid Game::gameInit() {
    int state;
    cout << "Utiliser un fichier (1) ou configurer manuellement (2) ? ";
    cin >> state;

    string outputFolder;
    Grid grid; // Déclaré ici pour être accessible après les blocs conditionnels.

    if (state == 1) {
        string fileName;
        cout << "Entrez le chemin du fichier source : ";
        cin >> fileName;

        ifstream file(fileName);
        while (!file.is_open()) {
            cout << "Le fichier ne correspond pas." << endl;
            cout << "Veuillez entrer à nouveau le lien du fichier : ";
            cin >> fileName;
            file.open(fileName);
        }

        int rows, cols;
        file >> rows >> cols;
        grid = Grid(rows, cols); // Initialisation de grid pour un fichier source.
        grid.initGrid(state, fileName);
        outputFolder = fileName.substr(0, fileName.find_last_of('.'));
        outputFolder = outputFolder + "_out";
    } else {
        grid.initGrid(state); // Initialisation de grid manuelle.
        outputFolder = "manual_out";
    }

    grid.folderCheck(outputFolder);
    return grid;
}



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
    Grid grid = gameInit();
    if (!mode){
        gameTerminal(iterationAmount, outputFolder, grid);
    }
    else {
        gameGUI(iterationAmount, grid);
    }
};