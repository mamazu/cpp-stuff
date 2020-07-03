#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include "Food.cpp"
#include <iostream>
#include "Body.cpp"

float length(sf::Vector2f vector) {
    return std::hypot(vector.x, vector.y);
}

class Snake : public sf::CircleShape {
public:
    Snake(const sf::Vector2f &position, unsigned int size, std::string name) : name(std::move(name)), body(5) {
        updateRadius((float) size);
        setPosition(position);
        body.updateSize((float) size);
    }


    void setHeading(const sf::Vector2f target) {
        const auto distance = target - getPosition();
        const auto i = length(distance);
        if (i > 0) {
            direction = distance / i;
        }
    }

    bool eat(const Food &food) {
        const bool overlaps = overlapsCircle(food);
        if (overlaps) {
            updateRadius(getRadius() + 2);
            speed = std::max(speed * 0.98, 20.0);
        }

        return overlaps;
    }

    void updateRadius(float radius) {
        setRadius(radius);
        setOrigin(radius, radius);
        body.updateSize(getRadius());
    }

    bool overlapsCircle(const sf::CircleShape &shape) {
        const auto distance = length(shape.getPosition() - getPosition());

        return (distance < getRadius() + shape.getRadius());
    }

    void update(const float timeStep) {
        auto position = getPosition();
        setPosition(position + (direction * speed * timeStep));
        body.update(position, timeStep);
    }

    void drawSnake(sf::RenderWindow &window) {
        window.draw(*this);
        body.draw(window);
    }

private:
    float speed = 100;
    sf::Vector2f direction;
    std::string name;

    Body body;
};

