#pragma once

class Cell {
private:
    bool living;                                // Cell state : dead (0) or alive (1)
    bool obstacle;                              // Wether the cell is an obstacle (1) or not (0)

public:
    Cell();                                     // Default constructor
    Cell(bool living, bool obstacle);           // Constructor
    bool getState() const;                      // Return wether the cell is alive or dead
    bool getObstacle() const;                   // Return wether the cell is an obstacle or not
    void editState(bool state);                 // Set the cell state (alive or dead)
    void editObstacle(bool isObstacle);         // Set a cell as obstacle or not
};