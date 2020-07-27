#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "vector_math.h"

class Food {
public:
    Food();

    void seed(const unsigned int WIDTH, const unsigned int HEIGHT) {
        static std::random_device dev;
        static std::mt19937 rng(dev());
        static std::uniform_real_distribution<double> distW(1, WIDTH);
        static std::uniform_real_distribution<double> distH(1, HEIGHT);

        sprite.setPosition(distW(rng), distH(rng));
    }

    sf::Rect<float> getHitBox() const {
        auto hitBox = sprite.getGlobalBounds();
        hitBox.height *= .75;

        return hitBox;
    }

    void drawFood(sf::RenderWindow &window) const;

private:
    constexpr const static float size = 5;
    std::unique_ptr<sf::Texture> texture;
    sf::Sprite sprite;
};
