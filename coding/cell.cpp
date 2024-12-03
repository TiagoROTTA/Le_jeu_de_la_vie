#include "cell.hpp"

Cell::Cell() : living(false), obstacle(false) {}

Cell::Cell(bool living, bool obstacle = false) : living(living), obstacle(obstacle) {}

bool Cell::getState() const {
    return living;
}

void Cell::editState(bool state) {
    living = state;
}
