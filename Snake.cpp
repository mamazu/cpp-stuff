#pragma once

#include <SFML/Graphics.hpp>
#include "Food.cpp"
#include <iostream>
#include "Body.cpp"
#include "vector_math.h"

class Snake : public sf::CircleShape {
public:
    Snake(const sf::Vector2f &position, unsigned int size, std::string name) : name(std::move(name)), body(20) {
        updateRadius((float) size);
        setPosition(position);
        body.updateSize((float) size);
        body.setPosition(position);
    }

    void setHeading(const sf::Vector2f target) {
        direction = normalize(target - getPosition());
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
    float speed = 150;
    sf::Vector2f direction;
    std::string name;

    Body body;
    friend Body;
};

