#pragma once
#include <vector>
#include <string>
#include "cell.hpp"

using namespace std;

class Grid {
private:
    int sizeX, sizeY;                                       // Grid size on the X and Y axis
    vector<vector<Cell>> grid;                              // Actual grid
    vector<vector<Cell>> tmp;                               // Grid buffer (for n+1 generation update)
    string folderPath;                                      // Writing folder path

    void surroundingCheck(int posY, int posX);              // Check the amount of living cells around each cell and applies Conway's game of life rules
    bool folderExists(string folderPath);                   // Check if the specified folder exists
    bool createFolder(string folderPath);                   // Create a folder at the specified path

public:
    Grid(int sizeX = 20, int sizeY = 20);                   // Constructor
    void create();                                          // Initialize a grid full of dead cells
    bool getCellState(int posY, int posX) const;            // Return specified cell's state
    bool getCellObstacle(int posY, int posX) const;         // Return wether the specified cell is an obstacle
    void displayGrid()const;                                // Display current grid in terminal
    int getSizeX()const;                                    // Returns grid size on X axis
    int getSizeY()const;                                    // Returns grid size on Y axis
    void stateChange(int posX, int posY);                   // Changes cell state (alive <-> dead)
    void updateGrid(bool mode);                             // Update each cell's state based on game rules and given mode
    void initGrid(int state, string fileName=NULL);         // Initializes the grid with a starting configuration
    void folderCheck(string outputFolder);                  // Manages iterations and writing to files
    void changePath(string path);                           // Change writing folder path
    void clearGrid(int& generationCount);                   // Clear the grid: set each cells' state to dead
};