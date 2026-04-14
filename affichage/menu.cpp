#include "menu.hpp"
#include <iostream>

Menu::Menu(float width, float height) {
    // --- CHARGEMENT DU FOND ---
    if (!backgroundTexture.loadFromFile("data/menu.png")) { 
        std::cerr << "Erreur chargement image fond\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        
        // Optionnel : Redimensionner l'image pour qu'elle remplisse la fenêtre
        sf::Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(width / textureSize.x, height / textureSize.y);
    }

    // --- CHARGEMENT DE LA POLICE ---
    if (!font.loadFromFile("data/Super Kidpop.TTF")) {
        std::cerr << "Erreur police Menu\n";
    }

    // --- BOUTON JOUER ---
    playButton.setSize(sf::Vector2f(250.f, 60.f));
    playButton.setFillColor(sf::Color(242, 190, 67));
    playButton.setOutlineThickness(2);
    playButton.setOutlineColor(sf::Color::White);
    playButton.setPosition(width/2.f - 125.f, height/2.f - 80.f);
    
    playText.setFont(font);
    playText.setString("Jouer");
    playText.setCharacterSize(30);
    // Centrage automatique du texte sur le bouton
    sf::FloatRect pRect = playText.getLocalBounds();
    playText.setOrigin(pRect.left + pRect.width/2.f, pRect.top + pRect.height/2.f);
    playText.setPosition(playButton.getPosition().x + 125.f, playButton.getPosition().y + 30.f);

    // --- BOUTON PARAMÈTRES ---
    settingsButton.setSize(sf::Vector2f(250.f, 60.f));
    settingsButton.setFillColor(sf::Color(242, 190, 67));
    settingsButton.setOutlineThickness(2);
    settingsButton.setOutlineColor(sf::Color::White);
    settingsButton.setPosition(width/2.f - 125.f, height/2.f + 20.f);
    
    settingsText.setFont(font);
    settingsText.setString("Parametres");
    settingsText.setCharacterSize(30);
    // Centrage automatique
    sf::FloatRect sRect = settingsText.getLocalBounds();
    settingsText.setOrigin(sRect.left + sRect.width/2.f, sRect.top + sRect.height/2.f);
    settingsText.setPosition(settingsButton.getPosition().x + 125.f, settingsButton.getPosition().y + 30.f);
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(playButton);
    window.draw(playText);
    window.draw(settingsButton);
    window.draw(settingsText);
}

int Menu::handleButtonClick(sf::Vector2i mousePos) {
    sf::Vector2f m(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (playButton.getGlobalBounds().contains(m)) return 1; // Jouer
    if (settingsButton.getGlobalBounds().contains(m)) return 2; // Paramètres
    
    return 0;
}