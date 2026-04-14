#include <SFML/Graphics.hpp>
#include "menu.hpp"
#include "ecranparam.hpp"
#include  "ecranjeu.hpp" 

int main() {
    // 1. Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(700, 700), "Jeu de Bateau");
    window.setFramerateLimit(60);

    // 2. Initialisation des différentes classes
    Menu myMenu(700, 700);
    SettingsScreen mySettings(700, 700);
    GameScreen myGameScreen(700, 700);

    // 3. Gestion de l'état du jeu
    GameState currentState = GameState::Menu;
    sf::Clock gameClock;
    int score = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Gestion des clics de souris selon l'écran actuel
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (currentState == GameState::Menu) {
                    int choice = myMenu.handleButtonClick(mousePos);
                    if (choice == 1) { // JOUER
                        currentState = GameState::Playing;
                        gameClock.restart();
                        myGameScreen.reset();
                        score = 0;
                    } 
                    else if (choice == 2) { // PARAMETRES
                        currentState = GameState::Settings;
                    }
                } 
                else if (currentState == GameState::Settings) {
                    if (mySettings.isBackButtonClicked(mousePos)) {
                        currentState = GameState::Menu;
                    }
                }
                // Si tu es en GameOver, tu peux aussi ajouter un clic pour revenir au menu ici
            }
        }

        // --- LOGIQUE DE MISE À JOUR ---
        if (currentState == GameState::Playing) {
            float timeLeft = 60.0f - gameClock.getElapsedTime().asSeconds();
            if (timeLeft <= 0) {
                timeLeft = 0;
                myGameScreen.setGameOver(false, score);
                currentState = GameState::GameOver;
            }
            myGameScreen.updateUI(score, timeLeft);
        }

        // --- DESSIN ---
        window.clear(sf::Color::Black);

        switch (currentState) {
            case GameState::Menu:
                myMenu.draw(window);
                break;

            case GameState::Settings:
                mySettings.draw(window);
                break;

            case GameState::Playing:
                myGameScreen.draw(window);
                // TODO: Dessiner le bateau ici plus tard
                break;

            case GameState::GameOver:
                myGameScreen.draw(window); // Dessine l'écran de jeu + la plaque de fin
                break;
        }

        window.display();
    }

    return 0;
}