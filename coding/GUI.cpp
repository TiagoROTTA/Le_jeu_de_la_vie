
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>


using namespace sf;

GUI::GUI(int cellSize, int gridWidth, int gridHeight){
    RenderWindow window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    // Charger une police pour le texte
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font arial.ttf"); // Erreur si la police n'est pas trouvée
    }

    // Configurer le texte du compteur de générations
    Text generationText;
    generationText.setFont(font);
    generationText.setCharacterSize(20);
    generationText.setFillColor(Color::White);
    generationText.setPosition((gridWidth * cellSize) / 2 - 50, 5);  // Centré en haut
}



// Compter le nombre de cellules vivantes
int GUI::countLivingCells(Grid& grid) {
    int count = 0;
    for (int y = 0; y < grid.getSizeY(); ++y) {
        for (int x = 0; x < grid.getSizeX(); ++x) {
            if (grid[y][x].getState()){
                count += 1;
            }
        }
    }
    return count;
}

// Rendre la grille et le texte dans la fenêtre
void GUI::render(RenderWindow& window, Text& generationText, Grid& grid) {
    window.clear();

    // Rendre la grille
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (int y = 0; y < grid.getSizeY(); ++y) {
        for (int x = 0; x < grid.getSizeX(); ++x) {
            if (grid[y][x].getState()) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }

    // Mettre à jour et rendre le texte du compteur de générations
    generationText.setString("Generation: " + std::to_string(generationCount));
    window.draw(generationText);

    // Afficher le nombre de cellules vivantes
    int livingCells = countLivingCells();
    if (generationText.getFont() != nullptr) {
        livingCellsText.setFont(*generationText.getFont());
    }
    else {
        throw std::runtime_error("Font not initialized for generationText.");
    }
 // Déréférencer le pointeur
    livingCellsText.setCharacterSize(20);
    livingCellsText.setFillColor(Color::White);
    livingCellsText.setString("Living Cells: " + std::to_string(livingCells));
    livingCellsText.setPosition((grid.getsizeX() * cellSize) / 2 - 50, 35);  // Centré sous le compteur de générations
    window.draw(livingCellsText);


    window.display();
}


// Gérer les clics pour ajouter des cellules vivantes
void GUI::handleMouseClick(RenderWindow &window) {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        // Récupérer la position du clic
        Vector2i mousePos = Mouse::getPosition(window);
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;

        // Basculer l'état de la cellule (vivante/morte)
        if (x >= 0 && x < grid.getSizeX() && y >= 0 && y < grid.getSizeY()) {
            grid.stateChange(y, x);
            
            sleep(milliseconds(50));
        }
    }
}

// Placer un motif prédéfini au centre de la grille
void GUI::placePattern(const std::vector<std::vector<int>>& pattern) {
    int startX = gridWidth / 2 - pattern.size() / 2;
    int startY = gridHeight / 2 - pattern[0].size() / 2;

    for (int x = 0; x < pattern.size(); ++x) {
        for (int y = 0; y < pattern[x].size(); ++y) {
            if (pattern[x][y] == 1) {
                grid[(startX + x + gridWidth) % gridWidth][(startY + y + gridHeight) % gridHeight] = 1;
            }
        }
    }
}

// Motifs prédéfinis


void GUI::play(Grid& grid) {
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
                    grid.clearGrid();  // Effacer
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

        handleMouseClick(window);

        if (!isPaused) {
            grid.updateGrid();
        }

        render(window, generationText);

        sleep(milliseconds(pause));  // Délai
    }
}
