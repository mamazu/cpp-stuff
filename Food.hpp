#pragma once

#include <SFML/Graphics.hpp>
#include <random>

class Food : public sf::CircleShape {
public:
    Food();

    void seed(const unsigned int WIDTH, const unsigned int HEIGHT) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<double> distW(1, WIDTH);
        std::uniform_real_distribution<double> distH(1, HEIGHT);

        setPosition(distW(rng),distH(rng));
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
