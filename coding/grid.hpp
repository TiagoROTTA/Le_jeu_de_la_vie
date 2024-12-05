#pragma once
#include <vector>
#include <string>
#include "cell.hpp"

using namespace std;

class Grid {
private:
    int sizeX, sizeY;
    vector<vector<Cell>> grid;
    vector<vector<Cell>> tmp;
    string folderPath;


    void surroundingCheck(int posY, int posX); // Vérifie les voisins d'une cellule et applique les règles
    bool folderExists(string folderPath); // Vérifie si un dossier existe
    bool createFolder(string folderPath); // Crée un dossier

public:
    Grid(int sizeX = 20, int sizeY = 20);
    void create();
    bool getCellState(int posY, int posX) const; 
    void displayGrid()const;
    int getSizeX()const;
    int getSizeY()const;
    void stateChange(int posX, int posY);
    void updateGrid();
    void initGrid(int state, string fileName=NULL);
    void folderCheck(string outputFolder); 
    void changePath(string path);
    void clearGrid(int& generationCount);
};
