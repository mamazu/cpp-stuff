#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "vector_math.h"

class Body {
public:
    explicit Body(const size_t size) {
        addBodyParts(size);
    }

    void addBodyParts(const size_t size) {
        unsigned long startIndex = bodyParts.size();
        bodyParts.resize(startIndex + size);

        for (size_t i = 0; i < size; i++) {
            bodyParts[startIndex + i].setRadius(10);
            bodyParts[startIndex + i].setOrigin(10, 10);
        }
    }

    void setPosition(sf::Vector2f position) {
        for (size_t i = 0; i < bodyParts.size(); ++i) {
            bodyParts[i].setPosition(position + mult(sf::Vector2f(10, 10), (float) i));
        }
    }

    void updateSize(const float headSize) {
        float size = headSize;
        for (auto &body: bodyParts) {
            size *= .85;
            body.setRadius(size);
            body.setOrigin(size, size);
        }
    }

    void update(const sf::Vector2f headPosition, const float timeStep) {
        auto position = headPosition;
        auto nodeSpeed = 150;

        for (size_t i = 0; i < bodyParts.size(); ++i) {
            auto &bodyPart = bodyParts[i];
            const auto currentPosition = bodyPart.getPosition();

            const auto direction = position - currentPosition;

            nodeSpeed *= 0.98f;
            const auto rescaledDirection = mult(normalize(direction), timeStep * nodeSpeed);

            const auto &new_position = currentPosition + rescaledDirection;
            const auto previousRadius = (i > 1) ? bodyParts[i - 1].getRadius() : 0;
            if (length(direction) >= (bodyPart.getRadius() + previousRadius)) {
                bodyPart.setPosition(new_position);
            }
            position = new_position;
        }
    }

    void draw(sf::RenderWindow &window) const {
        for (const auto &body: bodyParts) {
            window.draw(body);
        }
    }

private:
    std::vector<sf::CircleShape> bodyParts;
};