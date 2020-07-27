#pragma once

#include <SFML/Graphics.hpp>

class GUI {
public:
    GUI() {
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }

    void drawGUI(sf::RenderWindow& window);
    unsigned int score = 0;
private:
    sf::Font font;
};
