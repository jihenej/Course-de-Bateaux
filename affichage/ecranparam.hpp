#ifndef ECRANPARAN_H
#define ECRANPARAN_H
#include <SFML/Graphics.hpp>

class SettingsScreen {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text instructionsText; 
    sf::RectangleShape backButton;
    sf::Text backText;

public:
    SettingsScreen(float width, float height);
    void draw(sf::RenderWindow& window);
    bool isBackButtonClicked(sf::Vector2i mousePos); 
};

#endif