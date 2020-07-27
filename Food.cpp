#include <SFML/Graphics.hpp>
#include "Food.hpp"

Food::Food() {
    texture = std::make_unique<sf::Texture>();
    texture->loadFromFile("../food.png");

    sprite = sf::Sprite(*texture);
    sprite.setScale(.25, .25);
    sprite.setPosition(100, 25);
}

void Food::drawFood(sf::RenderWindow &window) const {
#if DEBUG
        const auto hitBox = getHitBox();
        sf::RectangleShape hitBoxShape{{hitBox.width, hitBox.height}};
        hitBoxShape.setPosition(hitBox.left, hitBox.top);
        hitBoxShape.setOrigin(0, 0);
        window.draw(hitBoxShape);
#endif

    window.draw(sprite);
}

