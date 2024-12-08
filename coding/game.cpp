#include <iostream>
#include "game.hpp"
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "GUI.hpp"

using namespace std;

// Gamemode selection: terminal (0) or graphical interface (1)
void Game::getMode(){
    cout << "Chose the display mode :" << endl;
    cout << "0 : Terminal" << endl;
    cout << "1 : Graphical interface" << endl;
    cin >> mode;
};


// Game start: setting up the first generation
Grid Game::gameInit() {
    int state;
    cout << "Use a file (1) or configure manually (2) ? ";
    cin >> state;
    Grid grid;

    // Case 1: starting grid is stored in a file
    if (state == 1) {
        string fileName;
        cout << "Enter source file path: ";
        cin >> fileName;
        ifstream file(fileName);

        // Continuously prompt the user for a valid file path until the file is successfully opened
        while (!file.is_open()) {
            cout << "Failed to opened the file at the given path." << endl;
            cout << "Please enter the file path again: ";
            cin >> fileName;
            file.open(fileName);
        }

        // Creating the grid from the given source file
        int rows, cols;
        file >> rows >> cols;
        grid = Grid(rows, cols);
        grid.initGrid(state, fileName);
        outputFolder = fileName.substr(0, fileName.find_last_of('.'));
        outputFolder = outputFolder + "_out";
    } 
    
    // Case 2: manually creating the grid
    else {
        grid.initGrid(state);
        outputFolder = "manual_out";
    }

    // Create folder in terminal mode
    if (mode == 0){
        grid.folderCheck(outputFolder);
    }

    return grid;
}


// Displaying the game in terminal
void Game::gameTerminal(int iterationAmount, Grid& grid)const{
    for (int i = 0; i<iterationAmount; i++) {
        string filePath = outputFolder + "/iteration_" + to_string(i) + ".txt";
        grid.changePath(filePath);
        grid.updateGrid(mode);
        grid.displayGrid();
        this_thread::sleep_for(chrono::milliseconds(500));
        system("clear");
    }
};


// Displaying the game with a graphical interface
void Game::gameGUI(Grid& grid) const{
    GUI graphic(10, grid.getSizeX(), grid.getSizeY(), &grid);
    graphic.play();
    grid.updateGrid(mode);
}


// Manage grid creation and the way the game is displayed according to user's choices and Conway's game of life rules
void Game::gameLoop(){
    Grid grid = gameInit();

    if (!mode){
        int iterationAmount;
        cout << "Entrez le nombre d'itérations souhaité : " << endl;
        cin >> iterationAmount;
        gameTerminal(iterationAmount, grid);
    }

    else {
        gameGUI(grid);
    }
};