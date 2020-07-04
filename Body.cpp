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
            bodyParts[startIndex + i].setFillColor(sf::Color(255, 0, 255));
            bodyParts[startIndex + i].setRadius(10);
            bodyParts[startIndex + i].setOrigin(10, 10);
        }
    }

    void setPosition(sf::Vector2f position) {
        for (auto& bodyPart: bodyParts) {
            bodyPart.setPosition(position);
        }
    }

    void updateSize(const float headSize) {
        float size = headSize;
        for(auto& body: bodyParts) {
            size *= .85;
            body.setRadius(size);
            body.setOrigin(size, size);
        }
    }

    void update(const sf::Vector2f headPosition, const float timeStep) {
        auto position = headPosition;
        auto nodeSpeed = 150;

        for (auto& bodyPart : bodyParts) {
            const auto currentPosition = bodyPart.getPosition();

            const auto distance = position - currentPosition;
            nodeSpeed *= 0.9f;

            const auto direction = mult(normalize(distance), timeStep * nodeSpeed);

            bodyPart.setPosition(currentPosition + direction);
            position = bodyPart.getPosition();
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