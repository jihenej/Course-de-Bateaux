#include "Jeu.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;
void lancerJeu(){
    //Initialisation de l'horloge
    sf::Clock clock;
    //Création de la fenêtre
    int width = 1000;
    int height = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "The window");
    window.setFramerateLimit(60);
    //Initialisation de l'échelle
    const float scale = 20.0f;
    //Initialisaton moteur physique
    sim::physics::PhysicsEngine engine;
	//Créer un bateau
    sf::ConvexShape boat;
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
    int nb_collec = 5;
    srand(time(0));
    sf::CircleShape collectibles[nb_collec];
    for(int i=0;i<nb_collec;i++){
        collectibles[i].setRadius(10);
        collectibles[i].setFillColor(sf::Color(220, 220, 220));
        int randposX = rand()%(width-20);
        int randposY = rand()%(height-20);
        collectibles[i].setPosition(randposX,randposY);
    }
    //Créer rigidBody bateau
    sim::physics::RigidBody* RBboat = engine.createGenericBoat();
    RBboat->setPosition(pos.x,pos.y);
    //Créer modèle physique bateau
    sim::physics::DynamicModel model;
    //Initialisation RPM et angle
    double RPM=0;
    double degre=0;
    int RPM_change_speed = 1000;
    int degree_change_speed = 10;
    //boucle principale
	while(window.isOpen()){
        //Temps
        float deltaTime = clock.restart().asSeconds();
        //Fermer fenêtre
	    sf::Event event;
	    while (window.pollEvent(event)){
	        if(event.type == sf::Event::Closed)
	        window.close();
	    }
        //Refresh
	    window.clear(sf::Color(30, 60, 120));
        //Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(degre<30)
                degre+=degree_change_speed*deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(degre>-30)
                degre-=degree_change_speed*deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(RPM>-2000)
                RPM-=RPM_change_speed*deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(RPM<3000)
                RPM+=RPM_change_speed*deltaTime;
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
        //Dessiner le bateau
        boat.setPosition(state.position.x * scale, state.position.y * scale);
        boat.setRotation(state.yaw*180.0/3.14159);
        window.draw(boat);
        //Dessiner les obstacles
        for(int i=0;i<nb_collec;i++){
            window.draw(collectibles[i]);
        }
        //Afficher la fenêtre
        window.display();
        }
}