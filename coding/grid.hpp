#pragma once
#include <vector>
#include "cell.hpp"

using namespace std;

class Grid {
private:
    int sizeX, sizeY;
    vector<vector<Cell>> grid;
    vector<vector<Cell>> tmp;

public:
    Grid(int sizeX = 20, int sizeY = 20);
    void create();
    void surroundingCheck(int posX, int posY);
    void displayGrid()const;
    int getSizeX()const;
    int getSizeY()const;
    void stateChange(int posX, int posY);
    void updateGrid();
    int initGrid();
};
