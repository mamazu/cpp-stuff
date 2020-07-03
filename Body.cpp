#include <vector>
#include <SFML/Graphics.hpp>

class Body {
public:
    explicit Body(const size_t size) {
        addBodyParts(size);
        
        for (const auto& body : bodyParts) {
            const sf::Color &color = body.getFillColor();
            printf("%d, %d, %d \n", color.r, color.g, color.b);
        }
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

    void updateSize(const float headSize) {
        float size = headSize;
        for(auto& body: bodyParts) {
            size *= .8;
            body.setRadius(size);
            body.setOrigin(size, size);
        }
    }

    void update(const sf::Vector2f headPosition, const float timeStep) {
        auto position = headPosition;

        for (auto &bodyPart: bodyParts) {
            const auto &newPost = position + sf::Vector2{10.0f * timeStep / timeStep, 10.0f};
            bodyPart.setPosition(newPost);
            position = newPost;
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