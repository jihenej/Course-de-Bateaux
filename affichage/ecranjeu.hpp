#ifndef ECRANJEU_H
#define ECRANJEU_H

#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class GameScreen {
private:
    sim::physics::PhysicsEngine engine;
    sim::physics::RigidBody* RBboat;
    sim::physics::DynamicModel model;
    sf::ConvexShape boat;
    float scale = 20.0f;
    double RPM = 0;
    double degre = 0;

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
    void update(float deltaTime, float width, float height);
    void setGameOver(bool won, int finalScore);
    void draw(sf::RenderWindow& window);
    void reset();
};

#endif