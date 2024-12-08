#include "cell.hpp"

// Default constructor
Cell::Cell() : living(false), obstacle(false) {}

//Constructor
Cell::Cell(bool living, bool obstacle = false) : living(living), obstacle(obstacle) {}


// Return wether the cell is alive or dead
bool Cell::getState() const {
    return living;
}


// Return wether the cell is an obstacle
bool Cell::getObstacle() const {
    return obstacle;
}


// Set the cell state (alive or dead)
void Cell::editState(bool state) {
    living = state;
}


// Set the cell as obstacle or not
void Cell::editObstacle(bool isObstacle) {
    obstacle = isObstacle;
}