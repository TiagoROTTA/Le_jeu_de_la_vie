
#include "GUI.hpp"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace sf;

// Constructor
GUI::GUI(int cellSize , int gridWidth, int gridHeight, Grid* grid)
    : cellSize(cellSize),
      gridWidth(gridWidth),
      gridHeight(gridHeight),
      window(VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life"),
      grid(grid),
      generationCount(0),
      pause(100),
      isPaused(false) {}


// Count the amount of living cells
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


// Render the grid in a new window
void GUI::render() {
    window.clear();

    // Draw cells
    RectangleShape cell(Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    for (int y = 0; y < grid->getSizeY(); ++y) {
        for (int x = 0; x < grid->getSizeX(); ++x) {
            if (grid->getCellState(y, x)) { // Consider living cells only
                cell.setPosition(x * cellSize, y * cellSize);   // Visually place the cell on the interface, according to its coordinates
                if (grid->getCellObstacle(y, x)){
                    cell.setFillColor(Color::Red);  // Obstacle cells will be red
                }else{
                    cell.setFillColor(Color::Green);    // Non obstacle living cells will be green
                }
                window.draw(cell);
            }
        }
    }
    // Display the whole grid
    window.display();
}


// Handle mouse clicks to add living cells manually
void GUI::handleMouseClick() {
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i mousePos = Mouse::getPosition(window); // Get mouse position and make it correspond to a cell
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;

        if (x >= 0 && x < grid->getSizeX() && y >= 0 && y < grid->getSizeY()) {
            grid->stateChange(y, x); // Switch cell's state upon clicking
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Anti bouncing command
        }
    }
}


// Place set patterns (glider, canon, ship, pulsar, acorn)
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


// Main method to play the game
void GUI::play() {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    isPaused = !isPaused;               // Pressing space will pause/unpause the game
                }
                if (event.key.code == Keyboard::C) {
                    grid->clearGrid(generationCount);   // Pressing C will clear the grid
                }
                if (event.key.code == Keyboard::Num1) {
                    placePattern(glider);               // Pressing 1 places a basic glider pattern
                }
                if (event.key.code == Keyboard::Num2) {
                    placePattern(canon);                // Pressing 2 places a canon pattern
                }
                if (event.key.code == Keyboard::Num3) {
                    placePattern(ship);                 // Pressing 3 places a ship pattern
                }
                if (event.key.code == Keyboard::Num5) {
                    placePattern(pulsar);               // Pressing 5 places a pulsar pattern
                }
                if (event.key.code == Keyboard::Num7) {
                    placePattern(a_corn);               // Pressing 7 places an acorn pattern
                }
                if (event.key.code == Keyboard::Add) {
                    pause -= 25;                        // Pressing + reduces the pause between 2 generations, thus making the game faster
                }
                if (event.key.code == Keyboard::Subtract) {
                    pause += 25;                        // On the opposite, pressing - makes the game slower
                }
            }
        }

        handleMouseClick();

        if (!isPaused) {
            grid->updateGrid(1);
        }

        render();

        std::this_thread::sleep_for(std::chrono::milliseconds(pause));  // Delay
    }
}