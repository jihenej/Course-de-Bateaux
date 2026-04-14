#include "ecranparam.hpp"
#include <iostream>

SettingsScreen::SettingsScreen(float width, float height) {

    // --- CHARGEMENT DU FOND ---
    if (!backgroundTexture.loadFromFile("data/param.png")) { 
        std::cerr << "Erreur chargement image fond\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        
        // Redimensionner l'image pour qu'elle remplisse la fenêtre
        sf::Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(width / textureSize.x, height / textureSize.y);
    }

    // --- CHARGEMENT DE LA POLICE ---
    if (!font.loadFromFile("data/Super Kidpop.TTF")) {
        std::cerr << "Erreur : Impossible de charger la police dans ecranparam.cpp\n";
    }

    // --- TEXTE DES INSTRUCTIONS ---
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(22);
    instructionsText.setFillColor(sf::Color(242, 190, 67));
    instructionsText.setString(
        "BUT DU JEU :\n\n"
        "Vous dirigez un bateau.\n"
        "Ramassez tous les objets le plus vite possible !\n"
        "Evitez les obstacles sur votre route.\n\n"
        "ATTENTION : Si le temps est ecoule avant\n"
        "d'avoir tout ramasse, c'est perdu !");
    
    // Positionnement du texte (pour fenêtre 700x700)
    instructionsText.setPosition(140.f, 220.f);

    // --- BOUTON RETOUR ---
    backButton.setSize(sf::Vector2f(200.f, 50.f));
    backButton.setFillColor(sf::Color(242, 190, 67)); 
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color::White);
    backButton.setPosition(width / 2.f - 100.f, height - 120.f); //position du buton

    // --- TEXTE DU BOUTON RETOUR ---
    backText.setFont(font);
    backText.setString("RETOUR");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::White);
    
    // Centrage du texte "RETOUR" précisément dans son bouton
    sf::FloatRect textRect = backText.getLocalBounds();
    backText.setOrigin(textRect.left + textRect.width / 2.f, 
                       textRect.top + textRect.height / 2.f);
    backText.setPosition(backButton.getPosition().x + 100.f, 
                         backButton.getPosition().y + 25.f);
}

void SettingsScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    // On dessine le texte d'explication
    window.draw(instructionsText);
    // On dessine le bouton et son texte
    window.draw(backButton);
    window.draw(backText);
}

bool SettingsScreen::isBackButtonClicked(sf::Vector2i mousePos) {
    // Conversion de la position de la souris en Vector2f pour la collision
    sf::Vector2f mouseF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    // Vérifie si le clic est à l'intérieur du rectangle du bouton
    return backButton.getGlobalBounds().contains(mouseF);
}