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
    void render(sf::RenderWindow &window, const Grid<WIDTH, HEIGHT> &grid) const;

    void setMovesLeft(const std::optional<unsigned int> movesLeft);

private:
    template<size_t WIDTH, size_t HEIGHT>
    void
    renderStats(sf::RenderWindow &window, const Grid<WIDTH, HEIGHT> &grid, int x, int y, const float tileSize) const;

    sf::Text centerText(std::string text, const int x, const int y, const float tileSize) const;

private:
    sf::Font font;
    const unsigned int fontSize = 30;
    std::optional<unsigned int> movesLeft;
};

void Renderer::setMovesLeft(const std::optional<unsigned int> movesLeft) {
    this->movesLeft = movesLeft;
}

template<size_t WIDTH, size_t HEIGHT>
void Renderer::render(sf::RenderWindow &window, const Grid<WIDTH, HEIGHT> &grid) const {
    const sf::Vector2u &size = window.getSize();
    const float tileSize = (float) std::min(size.x / WIDTH, size.y / HEIGHT);

    for (size_t i = 0; i < WIDTH * HEIGHT; ++i) {
        auto x = i % WIDTH;
        auto y = (int) (i / WIDTH);

        if (i == grid.getEmptySpot()) {
            if (movesLeft.has_value())
                window.draw(centerText("Moves left: \n" + std::to_string(movesLeft.value()), x, y, tileSize));

            continue;
        }

        sf::RectangleShape shape({tileSize, tileSize});

        shape.setPosition(x * tileSize, y * tileSize);
        shape.setOutlineColor(sf::Color::Blue);
        shape.setOutlineThickness(2);

        const sf::Text text = centerText(std::to_string(grid.get(x, y)), x, y, tileSize);

        window.draw(shape);
        window.draw(text);
    }
}

sf::Text Renderer::centerText(std::string textContent, const int x, const int y, const float tileSize) const {
    auto text = sf::Text{textContent, font, fontSize};
    text.setFillColor(sf::Color::Red);
    text.setPosition((float) (x + .5) * tileSize, (float) (y + .5) * tileSize);

    const auto textSize = text.getLocalBounds();
    text.setOrigin(textSize.left + textSize.width / 2, textSize.top + textSize.height / 2);

    return text;
}

#endif
