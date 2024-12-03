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
    void writeGridToFile(const vector<vector<Cell>>& grid, const string& filePath); // Écrit une grille dans un fichier
    bool folderExists(const string& folderPath); // Vérifie si un dossier existe
    bool createFolder(const string& folderPath); // Crée un dossier

public:
    Grid(int sizeX = 20, int sizeY = 20);
    void create();
    void displayGrid()const;
    int getSizeX()const;
    int getSizeY()const;
    void stateChange(int posX, int posY);
    void updateGrid();
    int initGrid();
    void runIterations(int numIterations, const string& outputFolder); // Exécute les itérations et sauvegarde les états
};
