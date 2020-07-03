#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Food : public sf::CircleShape {
public:
    Food() {
        setFillColor(sf::Color::Red);
        setOrigin(size, size);
        setRadius(size);
    }

    void seed(const unsigned int WIDTH, const unsigned int HEIGHT) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<double> distW(1, WIDTH);
        std::uniform_real_distribution<double> distH(1, HEIGHT);

        setPosition(distW(rng),distH(rng));
    }

private:
    constexpr const static float size = 5;
};
