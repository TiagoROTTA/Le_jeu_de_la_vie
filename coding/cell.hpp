#pragma once

class Cell {
private:
    bool living;                    // État de la cellule
    bool obstacle;                  // La cellule est un obstacle ou non 
public:
    Cell();                                     // Constructeur par défaut
    Cell(bool living, bool obstacle);   // Constructeur avec état initial
    bool getState() const;                      // Retourne l'état de la cellule
    bool getObstacle() const;                   // Retrouen si la cellule est un obstacle
    void editState(bool state);                 // Change l'état de la cellule
    void editObstacle(bool isObstacle);
};