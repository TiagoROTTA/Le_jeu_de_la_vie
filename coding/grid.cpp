#include "grid.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

// Constructeur : initialise la grille et le tampon temporaire
Grid::Grid(int sizeY, int sizeX) 
    : sizeX(sizeX), sizeY(sizeY), grid(sizeY, vector<Cell>(sizeX)), tmp(sizeY, vector<Cell>(sizeX)) {}

// Retourne la taille X de la grille
int Grid::getSizeX() const {
    return sizeX;
}

// Retourne la taille Y de la grille
int Grid::getSizeY() const {
    return sizeY;
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
            cout << (grid[i][j].getState() ? "O" : "."); // Affiche 'O' pour vivant, '.' pour mort
        }
        cout << endl;
    }
    cout << endl;
}

// Change l'état d'une cellule (vivante <-> morte)
void Grid::stateChange(int posY, int posX) {
    grid[posY][posX].editState(!grid[posY][posX].getState()); // Inverse l'état
}


void Grid::updateGrid() {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            surroundingCheck(i, j); // Calculer le nouvel état pour chaque cellule
        }
    }
    grid = tmp; // Remplacer la grille principale par le tampon
}


int Grid::initGrid() {
    int state;
    cout << "Utiliser un fichier (1) ou configurer manuellement (2) ? ";
    cin >> state;

    if (state == 1) {
        //create();
        string fileName;
        cout << "Entrez le chemin du fichier source : ";
        cin >> fileName;

        ifstream file(fileName);
        while (!file.is_open()) {
            cout << "Le fichier ne corespond pas" << endl;
            cout << "Veuillez entrer à nouveau le lien du fichier" << endl;
            cin >> fileName;
            ifstream file(fileName);
        }

        int rows, cols;
        file >> rows >> cols;
        sizeY = rows;
        sizeX = cols;
       /* if (rows != sizeY || cols != sizeX) {
            cerr << "Erreur : dimensions incompatibles." << endl;
            return 1;
        }*/
       create();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int value;
                file >> value;
                if (value == 1) stateChange(i, j);
            }
        }

        file.close();
        displayGrid();
        this_thread::sleep_for(chrono::milliseconds(1000));
    } else if (state == 2) {
        create();
        int posX, posY;
        cout << "Entrez les cellules vivantes (Y X). Tapez -1 -1 pour terminer." << endl;
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
    return 0;
}