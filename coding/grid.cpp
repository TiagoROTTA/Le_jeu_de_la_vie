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
    if (!grid[posY][posX].getObstacle()){
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


bool Grid::folderExists(const std::string& folderPath) {
    struct stat info;
    if (stat(folderPath.c_str(), &info) != 0) {
        return false; // Le dossier n'existe pas
    }
    return (info.st_mode & S_IFDIR) != 0; // Vérifie si c'est un dossier
}

bool Grid::createFolder(const std::string& folderPath) {
    // Commande système portable pour créer un dossier
    return mkdir(folderPath.c_str(), 0777) == 0 || errno == EEXIST;
}

void Grid::writeGridToFile(const std::vector<std::vector<Cell>>& grid, const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filePath << std::endl;
        return;
    }

    // Écriture des dimensions de la grille
    outFile << sizeY << " " << sizeX << "\n";

    // Écriture de l'état de chaque cellule
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            outFile << (cell.getState() ? 1 : 0) << " "; // 1 pour vivant, 0 pour mort
        }
        outFile << "\n";
    }

    outFile.close();
}
// Fonction pour gérer les itérations et l'écriture dans des fichiers
void Grid::runIterations(int numIterations, const string& outputFolder) {
    if (!folderExists(outputFolder)) {
        if (!createFolder(outputFolder)) {
            cerr << "Erreur : Impossible de créer le dossier " << outputFolder << endl;
            return;
        }
    }

    for (int iter = 0; iter < numIterations; ++iter) {
        string filePath = outputFolder + "/iteration_" + to_string(iter) + ".txt";
        writeGridToFile(grid, filePath); // Écrit l'état courant dans un fichier
        updateGrid(); // Met à jour la grille pour la prochaine itération
        this_thread::sleep_for(chrono::milliseconds(500)); // Pause pour visualiser l'évolution
    }

    cout << "État des " << numIterations << " premières itérations sauvegardé dans " << outputFolder << endl;
}

int Grid::initGrid() {
    int state;
    cout << "Utiliser un fichier (1) ou configurer manuellement (2) ? ";
    cin >> state;

    string outputFolder;

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
        sizeY = rows;
        sizeX = cols;
        create();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int value;
                file >> value;
                if (value == 1) stateChange(i, j);
            }
        }

        file.close();
        outputFolder = fileName + "_out";

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
        outputFolder = "manual_out";
    }

    int numIterations;
    cout << "Entrez le nombre d'itérations à exécuter : ";
    cin >> numIterations;

    runIterations(numIterations, outputFolder);
    return numIterations;
}