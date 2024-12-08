#include "grid.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <chrono>
#include <thread>

using namespace std;

// Constructor
Grid::Grid(int sizeY, int sizeX) 
    : sizeX(sizeX), sizeY(sizeY), grid(sizeY, vector<Cell>(sizeX)), tmp(sizeY, vector<Cell>(sizeX)), folderPath() {}


// Returns grid size on X axis
int Grid::getSizeX() const {
    return sizeX;
}


// Returns grid size on Y axis
int Grid::getSizeY() const {
    return sizeY;
}


// Change writing folder path
void Grid::changePath(string path){
    folderPath = path;
}


// Initialize a grid full of dead cells
void Grid::create() {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            grid[i][j] = Cell();    // Cells are dead and not obstacles by default
        }
    }
}


// Check the amount of living cells around each cell and applies Conway's game of life rules
void Grid::surroundingCheck(int posY, int posX) {

    // Obstacle cells will remain alive: game rules aren't applied to them
    if (grid[posY][posX].getObstacle()) {
        tmp[posY][posX].editState(true);
        tmp[posY][posX].editObstacle(true);
        return;
    }

    // Nearby alive cells counter
    int nearby = 0;

    // Get current state cell
    bool stateCell = grid[posY][posX].getState();

    // Go through the 8 nearby cells (3x3-1)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            // Ignore the checked cell in the count
            if (i == 0 && j == 0) continue;

            // Neighbor cell X and Y coordinates
            int neighborY = posY + i;
            int neighborX = posX + j;

            // Toric grid behavior: manage grid size overflow
            if (neighborY < 0) neighborY = sizeY - 1;
            if (neighborY >= sizeY) neighborY = 0;
            if (neighborX < 0) neighborX = sizeX - 1;
            if (neighborX >= sizeX) neighborX = 0;

            // Increment if the neighbor is alive
            if (grid[neighborY][neighborX].getState()) {
                nearby++;
            }
        }
    }

    // APPLYING GAME RULES
    
    // 2 or 3 alive neighbors: alive cell remains
    if (stateCell && (nearby == 2 || nearby == 3)) {
        tmp[posY][posX].editState(true);
    } 
    
    // Dead cell with 3 alive neighbors becomes alive
    else if (!stateCell && nearby == 3) {
        tmp[posY][posX].editState(true); 
    } 
    
    // Otherwise, cell dies or stays dead
    else {
        tmp[posY][posX].editState(false);
    }
}


// Display current grid in terminal
void Grid::displayGrid() const {
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {

            // Display 'X' for obstacle cells
            if (grid[i][j].getObstacle()) {
                cout << "X";
            } 
            
            // Display 'O' for alive cells and '.' for dead cells
            else {
                cout << (grid[i][j].getState() ? "O" : ".");
            }
        }
        cout << endl;
    }
    cout << endl;
}


// Changes cell state (alive <-> dead)
void Grid::stateChange(int posY, int posX) {
    grid[posY][posX].editState(!grid[posY][posX].getState());
}


// Changes if a cell is an obstacle
void Grid::obstacleChange(int posX, int posY){
    grid[posY][posX].editObstacle(!grid[posY][posX].getObstacle());
}


// Return specified cell's state
bool Grid::getCellState(int posY, int posX) const {
    return grid[posY][posX].getState();
}


// Return wether the specified cell is an obstacle
bool Grid::getCellObstacle(int posY, int posX) const {
    return grid[posY][posX].getObstacle();
}


// Update each cell's state based on game rules and given mode
void Grid::updateGrid(bool mode) {

    // Case 1: terminal mode, print the grid in a file
    if (!mode){
        ofstream outFile(this->folderPath);

        // Display an error message if the specified file can't be opened
        if (!outFile.is_open()) {
            cerr << "Error: can't open file " << this->folderPath << endl;
            return;
        }

        // Write grid dimensions to the file
        outFile << sizeY << " " << sizeX << "\n";

        // Update each cell's state and write the new state to the file
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                surroundingCheck(i, j);     // Update cell state based on neighbors
                outFile << (tmp[i][j].getState() ? 1 : 0) << " ";
            }
            outFile << "\n";
        }
        outFile.close();

    // Case 2: graphical mode
    }else{

        // Update each cell's state based on nearby alive cells
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                surroundingCheck(i, j);
            }
        }
    }

    // Replace the current grid with the updated grid (new generation)
    grid = tmp;
}


// Clear the grid: set each cells' state to dead
void Grid::clearGrid() {
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            grid[y][x].editState(false);
            grid[y][x].editObstacle(false);
            tmp[y][x].editState(false);      // Réinitialisation de tmp
            tmp[y][x].editObstacle(false);   // Réinitialisation des obstacles
        }
    }
}


bool Grid::folderExists(string folderpath) {
    struct stat info;   // System call that retrieves information about a file or directory

    // Converts STL C++ string folderpath to a C-style string, required by stat. Stores the metadata in info
    if (stat(folderpath.c_str(), &info) != 0) {
        return false;   // stat call failed: folder doesn't exist or permission issues
    }

    return (info.st_mode & S_IFDIR) != 0;   // Returns true if it's a folder, false otherwise
}


bool Grid::createFolder(string folderpath) {
    // System command to create a folder with the given name, granting read, write and execute permissions to the owner, displaying an error if it already exists 
    return mkdir(folderpath.c_str(), 0777) == 0 || errno == EEXIST; // Return true if the folder is correctly created or already exists
}


// Manages iterations and writing to files
void Grid::folderCheck(string outputFolder) {
    if (!folderExists(outputFolder)) {
        if (!createFolder(outputFolder)) {
            cerr << "Error: can't create folder " << outputFolder << endl;
            return;
        }
    }
}


// Initializes the grid with a starting configuration
void Grid::initGrid(int state, string fileName ) {

    // Case 1: Starting grid is defined in a file
    if (state == 1) {
        string value;

        ifstream file(fileName);

        // Create a grid of the specified size, initialized with dead cells
        create();

        // Read the grid configuration from the file
        for (int i = 0; i < sizeY; ++i) {
            for (int j = 0; j < sizeX; ++j) {
                int value;
                file >> value;

                // Update cell state based on file data
                if (value == 1) {
                    stateChange(i, j);  // Set the cell to alive
                } else if (value == 2) {
                    // Set the cell as an obstacle
                    grid[i][j].editState(true);   // Mark the cell as "alive"
                    grid[i][j].editObstacle(true);   // Flag the cell as an obstacle
                }

            }
        }

        file.close();   // Close the file after reading

    // Case 2: Starting grid is defined manually by user input
    } else if (state == 2) {
        // Create a grid of the specified size, initialized with dead cells
        create();
        
        cout << "Enter the coordinates of living cells (Y X). Enter -1 -1 to finish." << endl;

        int posX, posY;
        while (true) {
            cin >> posY >> posX;

            // Stop if user enters -1 -1
            if (posY == -1 && posX == -1) break;

            // Check if the entered coordinates are valid
            if (posY >= 0 && posY < sizeY && posX >= 0 && posX < sizeX) {
                stateChange(posY, posX);    // Set the specified cell to alive
            } else {
                cout << "Invalid coordinates. Please try again." << endl;
            }
        }   
    }
}