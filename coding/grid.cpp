#include "grid.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <chrono>
#include <thread>

using namespace std;

// Constructeur : initialise la grille et le tampon temporaire
Grid::Grid(int sizeY, int sizeX) 
    : sizeX(sizeX), sizeY(sizeY), grid(sizeY, vector<Cell>(sizeX)), tmp(sizeY, vector<Cell>(sizeX)), folderPath() {}

// Retourne la taille X de la grille
int Grid::getSizeX() const {
    return sizeX;
}

// Retourne la taille Y de la grille
int Grid::getSizeY() const {
    return sizeY;
}

void Grid::changePath(string path){
    folderPath = path;
}

// Initialise la grille avec des cellules mortes
void Grid::create() {
    
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            grid[i][j] = Cell(); // Toutes les cellules sont mortes au départ
        }
    }
}


// Vérifie les voisins d'une cellule et applique les règles du jeu
void Grid::surroundingCheck(int posY, int posX) {
    if (grid[posY][posX].getObstacle()) {
        // Une cellule obstacle reste vivante et immuable
        tmp[posY][posX].editState(true);
        tmp[posY][posX].editObstacle(true);
        return;
    }

    int nearby = 0; // Compteur de voisins vivants
    bool stateCell = grid[posY][posX].getState(); // État actuel de la cellule

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Ignorer la cellule elle-même

            int neighborY = posY + i;
            int neighborX = posX + j;

            // Gestion des débordements : coordonnées toroïdales
            if (neighborY < 0) neighborY = sizeY - 1;
            if (neighborY >= sizeY) neighborY = 0;
            if (neighborX < 0) neighborX = sizeX - 1;
            if (neighborX >= sizeX) neighborX = 0;

            if (grid[neighborY][neighborX].getState()) {
                nearby++; // Incrémenter si le voisin est vivant
            }
        }
    }


    // Appliquer les règles du jeu
    if (stateCell && (nearby == 2 || nearby == 3)) {
        tmp[posY][posX].editState(true); // Cellule vivante reste vivante
    } else if (!stateCell && nearby == 3) {
        tmp[posY][posX].editState(true); // Cellule morte devient vivante
    } else {
        tmp[posY][posX].editState(false); // Sinon, la cellule meurt ou reste morte
    }
    
}


// Affiche la grille actuelle dans la console
void Grid::displayGrid() const {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            if (grid[i][j].getObstacle()) {
                cout << "X"; // Affiche 'X' pour les obstacles
            } else {
                cout << (grid[i][j].getState() ? "O" : "."); // 'O' pour vivant, '.' pour mort
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Change l'état d'une cellule (vivante <-> morte)
void Grid::stateChange(int posY, int posX) {
    grid[posY][posX].editState(!grid[posY][posX].getState()); // Inverse l'état
}


bool Grid::getCellState(int posY, int posX) const {
    return grid[posY][posX].getState();
}

bool Grid::getCellObstacle(int posY, int posX) const {
    return grid[posY][posX].getObstacle();
}

void Grid::updateGrid(bool mode) {
    if (!mode){
        ofstream outFile(this->folderPath);
        if (!outFile.is_open()) {
            cerr << "Erreur : Impossible d'ouvrir le fichier " << this->folderPath << endl;
            return;
        }
        outFile << sizeY << " " << sizeX << "\n";

        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                surroundingCheck(i, j); // Calculer le nouvel état pour chaque cellule
                outFile << (tmp[i][j].getState() ? 1 : 0) << " ";
            }
            outFile << "\n";
        }
        outFile.close();
    }else{
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                surroundingCheck(i, j); // Calculer le nouvel état pour chaque cellule
            }
        }
    }
    grid = tmp; // Remplacer la grille principale par le tampon
}


// Effacer la grille (toutes les cellules mortes)
void Grid::clearGrid(int& generationCount) {
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            grid[y][x].editState(false);
        }
    }
    generationCount = 0;  // Réinitialiser le compteur
}


bool Grid::folderExists(string folderpath) {
    struct stat info;
    if (stat(folderpath.c_str(), &info) != 0) {
        return false; // Le dossier n'existe pas
    }
    return (info.st_mode & S_IFDIR) != 0; // Vérifie si c'est un dossier
}

bool Grid::createFolder(string folderpath) {
    // Commande système portable pour créer un dossier
    return mkdir(folderpath.c_str(), 0777) == 0 || errno == EEXIST;
}


// Fonction pour gérer les itérations et l'écriture dans des fichiers
void Grid::folderCheck(string outputFolder) {
    if (!folderExists(outputFolder)) {
        if (!createFolder(outputFolder)) {
            cerr << "Erreur : Impossible de créer le dossier " << outputFolder << endl;
            return;
        }
    }
}


void Grid::initGrid(int state, string fileName ) {

    if (state == 1) {
        string value;

        ifstream file(fileName);

        create();

        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                int value;
                file >> value;
                if (value == 1) {
                    stateChange(i, j);
                } else if (value == 2) {
                    grid[i][j].editState(true);   // Une cellule obstacle est vivante
                    grid[i][j].editObstacle(true);   // Est marquée comme un obstacle
                }

            }
        }

        file.close();

    } else if (state == 2) {
        create();
        cout << "Entrez les cellules vivantes (Y X). Tapez -1 -1 pour terminer." << endl;
        int posX, posY;
        while (true) {
            cin >> posY >> posX;
            if (posY == -1 && posX == -1) break;
            if (posY >= 0 && posY < sizeY && posX >= 0 && posX < sizeX) {
                stateChange(posY, posX);
            } else {
                cout << "Coordonnées invalides." << endl;
            }
        }
        
    }
}