#pragma once

class Cell {
private:
    bool living;                    // État de la cellule
public:
    Cell();                          // Constructeur par défaut
    Cell(bool living);               // Constructeur avec état initial
    bool getState() const;           // Retourne l'état de la cellule
    void editState(bool state);      // Change l'état de la cellule
};
