#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.cpp"
#include "Food.hpp"
#include "GUI.h"

std::vector<Food> instanciateFoods(const size_t count, const unsigned int width, const unsigned int height) {
    std::vector<Food> foods;
    foods.resize(count);
    for (size_t i = 0; i < count; ++i) {
        Food food;
        food.seed(width, height);
        foods[i] = std::move(food);
    }

    return foods;
}

int main() {
    unsigned int width = 800;
    unsigned int height = 800;

    sf::RenderWindow window(sf::VideoMode(width, height), "Snake something");
    Snake snake{sf::Vector2f{(float) width / 2, (float) height / 2}, 10, "Player"};
    GUI gui;

    auto foods = instanciateFoods(1, width, height);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                width = event.size.width;
                height = event.size.height;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        const auto mousePos = sf::Mouse::getPosition(window);
        if (mousePos.x >= 0 && mousePos.y >= 0) {
            snake.setHeading(sf::Vector2f{(float) mousePos.x, (float) mousePos.y});
        }

        snake.update(clock.getElapsedTime().asSeconds());

        for (auto &food : foods) {
            if (snake.eat(food)) {
                food.seed(width, height);
                gui.score++;
            }
        }

        clock.restart();


        // Drawing logic
        window.clear(sf::Color(0, 0, 255));
        for (const auto &food: foods) {
            food.drawFood(window);
        }
        snake.drawSnake(window);

        gui.drawGUI(window);

        window.display();
    }

    return 0;
}