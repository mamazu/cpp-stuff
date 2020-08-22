#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"
#include "Renderer.h"
#include "Solver.h"

constexpr size_t GRID_WIDTH = 4;
constexpr size_t GRID_HEIGHT = 4;

int main() {
    unsigned int width = 800;
    unsigned int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "Swapper");

    Grid<GRID_WIDTH, GRID_HEIGHT> grid(0, 0);
    for(size_t i = 0; i < 100; i++) {
        switch((rand() % 4)) {
            case 0:
                grid.swap(NORTH);
                break;
            case 1:
                grid.swap(EAST);
                break;
            case 2:
                grid.swap(SOUTH);
                break;
            case 3:
                grid.swap(WEST);
                break;
        }
    }

    Renderer renderer;
    Solver solver;

    const Moves &vector = solver.solve(grid);
    printf("Moves: %i", (int) vector.size());
    for(auto move: vector) {
        auto moveString = "";
        switch (move) {
            case NORTH:
                moveString =  "North";
                break;
            case EAST:
                moveString =  "East";
                break;
            case WEST:
                moveString =  "West";
                break;
            case SOUTH:
                moveString =  "South";
                break;
            default:
                moveString =  "Nope";
        }

        puts(moveString);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                width = event.size.width;
                height = event.size.height;
                window.setView(sf::View{sf::FloatRect{0, 0, (float) width, (float) height}});
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                grid.swap(WEST);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
               grid.swap(EAST);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                grid.swap(NORTH);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                grid.swap(SOUTH);
            }
        }

        window.clear();
        renderer.render(window, grid);
        window.display();
    }

    return 0;
}