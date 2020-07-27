#include "GUI.h"

static sf::Text drawScore(unsigned int score, sf::Font &font) {
    constexpr unsigned int fontSize = 30;
    return sf::Text{"Score: " + std::to_string(score), font, fontSize};
}

void GUI::drawGUI(sf::RenderWindow &window) {
    window.draw(drawScore(score, font));
}
