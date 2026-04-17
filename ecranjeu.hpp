#ifndef ECRANJEU_H
#define ECRANJEU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"
#include <iostream>
using namespace std;

class GameScreen {
private:
    // Elements graphiques
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

    // Collectibles
    int nb_collec;
    int nb_restants;
    sf::CircleShape* collectibles;

    // GameOver
    bool isGameOver;

    // Modèle physique bateau
    sf::ConvexShape boat;
    sim::physics::PhysicsEngine engine;
    sim::physics::RigidBody* RBboat;
    sim::physics::DynamicModel model;

    // RPM et angle
    double RPM=0;
    double degre=0;
    int RPM_change_speed = 1000;
    int degree_change_speed = 40;

    // Score
    int score=0;

public:
    GameScreen(float width, float height, int nb);
    ~GameScreen();
    void updateUI(int score, float timeLeft);
    void setGameOver(bool won, int finalScore);
    void draw(sf::RenderWindow& window);
    void reset();
    void Initialize(int,int);
    void UpdateGame(float,int,int,float);
    int GetNbObstacle();
    int GetScore();
};

#endif