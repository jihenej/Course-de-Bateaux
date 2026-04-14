#include "ecranjeu.hpp"
#include <iostream>

GameScreen::GameScreen(float width, float height) : isGameOver(false) {
    // --- CHARGEMENT DU FOND ---
    if (!backgroundTexture.loadFromFile("data/jeu.png")) { 
        std::cerr << "Erreur chargement image fond\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
        
        // Optionnel : Redimensionner l'image pour qu'elle remplisse la fenêtre
        sf::Vector2u textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(width / textureSize.x, height / textureSize.y);
    }

    // --- CHARGEMENT DE LA POLICE ---
    if (!font.loadFromFile("data/Super Kidpop.TTF")) {
        std::cerr << "Erreur police GameScreen\n";
    }

    // UI en haut
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(30.f, 20.f);

    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::Yellow);
    timerText.setPosition(width - 200.f, 20.f);

    // Plaque de fin (centrée sur 700x700)
    endPlate.setSize(sf::Vector2f(400.f, 300.f));
    endPlate.setFillColor(sf::Color(50, 50, 50, 230));
    endPlate.setOutlineThickness(5);
    endPlate.setOutlineColor(sf::Color::White);
    endPlate.setPosition(width/2.f - 200.f, height/2.f - 150.f);

    resultText.setFont(font);
    resultText.setCharacterSize(50);
    resultText.setPosition(width/2.f - 100.f, height/2.f - 120.f);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setPosition(width/2.f - 80.f, height/2.f + 20.f);
}

void GameScreen::updateUI(int score, float timeLeft) {
    scoreText.setString("Score: " + std::to_string(score));
    timerText.setString("Temps: " + std::to_string(static_cast<int>(timeLeft)) + "s");
}

void GameScreen::setGameOver(bool won, int finalScore) {
    isGameOver = true;
    if (won) {
        resultText.setString("GAGNE !");
        resultText.setFillColor(sf::Color::Green);
    } else {
        resultText.setString("PERDU !");
        resultText.setFillColor(sf::Color::Red);
    }
    finalScoreText.setString("Score Final: " + std::to_string(finalScore));
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(scoreText);
    window.draw(timerText);

    if (isGameOver) {
        window.draw(endPlate);
        window.draw(resultText);
        window.draw(finalScoreText);
    }
}

void GameScreen::reset() {
    isGameOver = false;
}