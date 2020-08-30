#include <SFML/Graphics.hpp>
#include <iostream>
#include "Renderer.h"
#include "Grid.h"
#include "Animator.hpp"

constexpr size_t GRID_WIDTH = 4;
constexpr size_t GRID_HEIGHT = 4;

int main() {
    unsigned int width = 800;
    unsigned int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "Swapper");

    Grid<GRID_WIDTH, GRID_HEIGHT> grid(0, 0);

    Renderer renderer;
    Animator animator;

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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                animator.solve(grid);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){
                animator.increaseSpeed();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){
                animator.decreaseSpeed();
            }
        }

        animator.update(grid);
        window.clear();
        renderer.setMovesLeft(animator.getMovesLeft());
        renderer.render(window, grid);
        window.display();
    }

    return 0;
}