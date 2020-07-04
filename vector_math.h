# pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

[[nodiscard]] float length(const sf::Vector2f& vector) {
    return std::hypot(vector.x, vector.y);
}

[[nodiscard]] sf::Vector2f div(const sf::Vector2f& vector, const float f) {
    return sf::Vector2f{vector.x / f, vector.y / f};
}

[[nodiscard]] sf::Vector2f mult(const sf::Vector2f& vector, const float f) {
    return sf::Vector2f{vector.x * f, vector.y * f};
}

[[nodiscard]] sf::Vector2f normalize(const sf::Vector2f& vector) {
    const float len = length(vector);
    if (len != 0) {
        return div(vector, len);
    }
    return vector;
}

void printf(const sf::Vector2f& vector) {
    printf("%f|%f\n", vector.x, vector.y);
}