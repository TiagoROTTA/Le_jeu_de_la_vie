
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>


using namespace sf;

GUI::GUI(int cellSize , int gridWidth, int gridHeight, Grid* grid)
    : cellSize(cellSize),
      gridWidth(gridWidth),
      gridHeight(gridHeight),
      window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life"),
      grid(grid),
      generationCount(0),
      pause(100),
      isPaused(false) {}



// Compter le nombre de cellules vivantes
int GUI::countLivingCells() {
    int count = 0;
    for (int y = 0; y < grid->getSizeY(); ++y) {
        for (int x = 0; x < grid->getSizeX(); ++x) {
            if (grid->getCellState(y, x)) {
                count++;
            }
        }
    }
    return count;
}

// Rendre la grille et le texte dans la fenêtre
void GUI::render() {
    window.clear();

    // Dessiner les cellules
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (int y = 0; y < grid->getSizeY(); ++y) {
        for (int x = 0; x < grid->getSizeX(); ++x) {
            if (grid->getCellState(y, x)) { // Accéder à l'état d'une cellule
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(Color::Green);
                window.draw(cell);
            }
        }
    }

    // Texte : Génération actuelle
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font arial.ttf");
    }

    Text generationText;
    generationText.setFont(font);
    generationText.setString("Generation: " + std::to_string(generationCount));
    generationText.setCharacterSize(20);
    generationText.setFillColor(Color::White);
    generationText.setPosition(10, 10);
    window.draw(generationText);

    // Texte : Nombre de cellules vivantes
    Text livingCellsText;
    livingCellsText.setFont(font);
    livingCellsText.setString("Living Cells: " + std::to_string(countLivingCells()));
    livingCellsText.setCharacterSize(20);
    livingCellsText.setFillColor(Color::White);
    livingCellsText.setPosition(10, 40);
    window.draw(livingCellsText);

    // Afficher tout
    window.display();
}


// Gérer les clics pour ajouter des cellules vivantes
void GUI::handleMouseClick() {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition(window);
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;

        if (x >= 0 && x < grid->getSizeX() && y >= 0 && y < grid->getSizeY()) {
            grid->stateChange(y, x); // Basculer l'état de la cellule
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void GUI::placePattern(const std::vector<std::vector<int>>& pattern) {
    int startX = gridWidth / 2 - pattern.size() / 2;
    int startY = gridHeight / 2 - pattern[0].size() / 2;

    for (int x = 0; x < pattern.size(); ++x) {
        for (int y = 0; y < pattern[x].size(); ++y) {
            if (pattern[x][y] == 1) {
                int wrappedX = (startX + x + gridWidth) % gridWidth;
                int wrappedY = (startY + y + gridHeight) % gridHeight;
                grid->stateChange(wrappedY, wrappedX);
            }
        }
    }
}

// Motifs prédéfinis


void GUI::play() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    isPaused = !isPaused;  // Pause
                }
                if (event.key.code == Keyboard::C) {
                    grid->clearGrid(generationCount);  // Effacer
                }
                if (event.key.code == Keyboard::Num1) {
                    placePattern(glider);
                }
                if (event.key.code == Keyboard::Num2) {
                    placePattern(canon);
                }
                if (event.key.code == Keyboard::Num3) {
                    placePattern(ship);
                }
                if (event.key.code == Keyboard::Num5) {
                    placePattern(pulsar);
                }
                if (event.key.code == Keyboard::Num7) {
                    placePattern(a_corn);
                }
                if (event.key.code == Keyboard::Add) {
                    pause -= 25;
                }
                if (event.key.code == Keyboard::Subtract) {
                    pause += 25;
                }
            }
        }

        handleMouseClick();

        if (!isPaused) {
            grid->updateGrid(1);
        }

        render();

        std::this_thread::sleep_for(std::chrono::milliseconds(pause));  // Délai
    }
}
