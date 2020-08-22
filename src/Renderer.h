#ifndef PLATFORMER_RENDERER_H
#define PLATFORMER_RENDERER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include "Grid.h"

class Renderer {
public:
    explicit Renderer() {
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    template<size_t WIDTH, size_t HEIGHT>
    void render(sf::RenderWindow& window, const Grid<WIDTH, HEIGHT> &grid) const;

private:
    sf::Font font;
};

template<size_t WIDTH, size_t HEIGHT>
void Renderer::render(sf::RenderWindow& window, const Grid<WIDTH, HEIGHT> &grid) const {
    const auto fontSize = 30;
    const sf::Vector2u &size = window.getSize();
    auto tileSize = (float) std::min(size.x / WIDTH, size.y / HEIGHT);

    for(size_t i = 0; i < WIDTH * HEIGHT; ++i) {
        if (i == grid.getEmptySpot()) {
            continue;
        }

        sf::RectangleShape shape({tileSize, tileSize});

        auto x = i % WIDTH;
        auto y = (int) (i / WIDTH);

        shape.setPosition(x * tileSize, y * tileSize);
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(2);

        auto text = sf::Text{std::to_string(grid.get(x, y)), font, fontSize};
        text.setFillColor(sf::Color::Red);
        text.setPosition((float) (x + .5) * tileSize, (float) (y + .5) * tileSize);

        const auto textSize = text.getLocalBounds();
        text.setOrigin(textSize.left + textSize.width/2,textSize.top + textSize.height / 2);

        window.draw(shape);
        window.draw(text);
    }
}
#endif
