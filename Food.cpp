#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Food : public sf::CircleShape {
public:
    Food() {
        setOrigin(size, size);
        setRadius(size);

        texture = std::make_unique<sf::Texture>();
        texture->loadFromFile("../food.png");

        sprite = sf::Sprite(*texture);
        sprite.setScale(.25, .25);
        sprite.setPosition(100, 25);
    }

    void seed(const unsigned int WIDTH, const unsigned int HEIGHT) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<double> distW(1, WIDTH);
        std::uniform_real_distribution<double> distH(1, HEIGHT);

        setPosition(distW(rng),distH(rng));
    }

    void drawFood(sf::RenderWindow &window) const
    {
        window.draw(sprite);
    }

private:
    constexpr const static float size = 5;
    std::unique_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};
