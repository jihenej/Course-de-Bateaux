#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

// On garde l'enum ici ou dans un fichier global Types.hpp
enum class GameState { Menu, Settings, Playing, GameOver };

class Menu {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;

    // Éléments du Menu Principal uniquement
    sf::RectangleShape playButton;
    sf::Text playText;
    sf::RectangleShape settingsButton;
    sf::Text settingsText;

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    // Renvoie 1 pour Jouer, 2 pour Paramètres, 0 sinon
    int handleButtonClick(sf::Vector2i mousePos);
};

#endif