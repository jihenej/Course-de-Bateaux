#include "ecranjeu.hpp"
#include <iostream>

GameScreen::GameScreen(float width, float height, int nb) : isGameOver(false) {
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

    //Créer un bateau
    boat.setPointCount(6);
    boat.setPoint(0, sf::Vector2f(40, 0));    
    boat.setPoint(1, sf::Vector2f(10, 15));   
    boat.setPoint(2, sf::Vector2f(-20, 12));  
    boat.setPoint(3, sf::Vector2f(-35, 0));   
    boat.setPoint(4, sf::Vector2f(-20, -12)); 
    boat.setPoint(5, sf::Vector2f(10, -15));  
    boat.setFillColor(sf::Color(220, 220, 220));
    boat.setOutlineThickness(2);
    boat.setOutlineColor(sf::Color::White);
    sf::Vector2f pos = {5.0,5.0};
    //Créer objet à collecter
    nb_collec = nb;
    nb_restants = nb_collec;
    collectibles = new sf::CircleShape[nb_collec];
    srand(time(0));
    for(int i=0;i<nb_collec;i++){
        collectibles[i].setRadius(10);
        collectibles[i].setFillColor(sf::Color(220, 220, 220));
        int randposX = rand()%(int)(width-20);
        int randposY = rand()%(int)(height-20);
        collectibles[i].setPosition(randposX,randposY);
    }
    //Créer rigidBody bateau
    RBboat = engine.createGenericBoat();
    RBboat->setPosition(pos.x,pos.y);
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

void GameScreen::UpdateGame(float deltaTime, int width, int height, float scale){
    //Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(degre<60)
                degre+=degree_change_speed*deltaTime;
        }
        else{
            if(degre>0)
                degre-=(degree_change_speed/2)*deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(degre>-60)
                degre-=degree_change_speed*deltaTime;
        }
        else{
            if(degre<0)
                degre+=(degree_change_speed/2)*deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(RPM>-2000)
                RPM-=RPM_change_speed*deltaTime;
        }
        else{
            if(RPM<0)
                RPM+=(RPM_change_speed/2)*deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(RPM<3000)
                RPM+=RPM_change_speed*deltaTime;
        }
        else{
            if(RPM>0)
                RPM-=(RPM_change_speed/2)*deltaTime;
        }
        //Calculer et appliquer les forces au bateau
        sim::common::ForceTorque2D damping = model.computeDamping(*RBboat,1026);
        sim::common::ForceTorque2D addedMass = model.computeAddedMass(*RBboat);
        sim::common::ForceTorque2D actuators = model.computeActuators(*RBboat,RPM,degre,1026);
        RBboat->addForce(damping);
        RBboat->addForce(addedMass);
        RBboat->addForce(actuators);
        //Récupérer l'état du bateau
        const auto& state = RBboat->getState();
        // --- WRAP SCREEN ---
        double newX = state.position.x;
        double newY = state.position.y;
        bool out = false;
        if (newX * scale > width) { newX = 0; out = true; }
        if (newX * scale < 0)    { newX = width / scale; out = true; }
        if (newY * scale > height)  { newY = 0; out = true; }
        if (newY * scale < 0)    { newY = height / scale; out = true; }
        if (out) {
            RBboat->setPosition(newX, newY);
        }
        //Faire avancer la simulation
        engine.step(deltaTime);
        boat.setPosition(state.position.x * scale, state.position.y * scale);
        boat.setRotation(state.yaw*180.0/3.14159);
}

void GameScreen::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(scoreText);
    window.draw(timerText);
    window.draw(boat);
    //Dessiner les obstacles et tester collision avec le bateau
    for(int i=0;i<nb_collec;i++){
        int result = boat.getGlobalBounds().intersects(collectibles[i].getGlobalBounds());
        if(result){
            collectibles[i].setRadius(0);
            nb_restants--;
            score++;
        }
        if(collectibles[i].getRadius()!=0)
            window.draw(collectibles[i]);
    }
    if (isGameOver) {
        window.draw(endPlate);
        window.draw(resultText);
        window.draw(finalScoreText);
    }
}

int GameScreen::GetNbObstacle(){
    return nb_restants;
}

int GameScreen::GetScore(){
    return score;
}

void GameScreen::reset() {
    isGameOver = false;
}

GameScreen ::~GameScreen(){
    delete [] collectibles;
}