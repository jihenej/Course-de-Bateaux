#include <SFML/Graphics.hpp>

#include "physics/dynamicModel.h"
#include "physics/physicsEngine.h"

#include <iostream>

class SIMRACE_DLL Rigidody {
  public:
    RigideBody(ModelConfig& config);
    void addForce(common::ForceTorque2D& force);
    const common::ForceTorque2D getForce() const;
    const state& getState() const;
    const ModelConfig& getModel() const;

};

int main()
{
	sf::Clock clock;
	
	std::cout << "Everything OK" << std::endl;
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "The window");
	
	//Définir un carré 
	sf::RectangleShape square(sf::Vector2f(50, 50));
        square.setFillColor(sf::Color(100, 250, 50));
        
	while(window.isOpen()){
	//Création de la fenêtre
	  sf::Event event;
	  while (window.pollEvent(event)){
	    if(event.type == sf::Event::Closed)
	      window.close();
	  }
	  window.clear(sf::Color::Black);
	  
          // Dessiner un carré
          window.draw(square);
	  
	  //Bouger un carré
	  float deltaTime = clock.restart().asSeconds();
          float speed = 200.0f; // pixels par seconde
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
                  square.move(-speed * deltaTime, 0);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
                  square.move(speed * deltaTime, 0);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
                  square.move(0, -speed * deltaTime);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
                  square.move(0, speed * deltaTime);
          }
	  
	  sf::Vector2u windowSize = window.getSize();
          sf::Vector2f pos = square.getPosition();
          sf::Vector2f size = square.getSize();

          if (pos.x < 0)
              pos.x = 0;
          if (pos.x + size.x > windowSize.x)
              pos.x = windowSize.x - size.x;

          if (pos.y < 0)
              pos.y = 0;
          if (pos.y + size.y > windowSize.y)
              pos.y = windowSize.y - size.y;

          square.setPosition(pos);
	  
	  window.display();
	 } 
	 
	 
	return 0;
}
