#include <SFML/Graphics.hpp>
#include "Food.hpp"

Food::Food() {
    setOrigin(size, size);
    setRadius(size);

    texture = std::make_unique<sf::Texture>();
    texture->loadFromFile("../food.png");

    sprite = sf::Sprite(*texture);
    sprite.setScale(.25, .25);
    sprite.setPosition(100, 25);
}

void Food::drawFood(sf::RenderWindow &window) const {
#if DEBUG
        static const auto hitBox = getHitBox();
        static sf::RectangleShape hitBoxShape{{hitBox.width, hitBox.height}};
        hitBoxShape.setPosition(hitBox.left, hitBox.top);
        hitBoxShape.setOrigin(0, 0);
        window.draw(hitBoxShape);
#endif

    window.draw(sprite);
}

