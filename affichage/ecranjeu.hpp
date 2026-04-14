#ifndef ECRANJEU_H
#define ECRANJEU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class GameScreen {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font font;
    
    // UI en jeu
    sf::Text scoreText;
    sf::Text timerText;

    // Plaque de fin
    sf::RectangleShape endPlate;
    sf::Text resultText;
    sf::Text finalScoreText;
    
    bool isGameOver;

public:
    GameScreen(float width, float height);
    void updateUI(int score, float timeLeft);
    void setGameOver(bool won, int finalScore);
    void draw(sf::RenderWindow& window);
    void reset();
};

#endif