#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Scene.h"

class MainMenu : public Scene
{
public:
    MainMenu(const std::string& sceneName, sf::RenderWindow* _window);

    void Render(sf::RenderWindow* _window);
    int Update(sf::RenderWindow* _window);

private:
    Button* jouerButton = nullptr;
    Button* optionsButton = nullptr;
    Button* quitterButton = nullptr;

    sf::RenderWindow* window;
};

MainMenu::MainMenu(const std::string& sceneName, sf::RenderWindow* _window)
    : Scene(sceneName), window(_window)
{
    // Création des boutons
    jouerButton = new Button(window, Maths::Vector2f(0.3f, 0.1f), "Jouer", sf::Color::White);
    optionsButton = new Button(window, Maths::Vector2f(0.3f, 0.1f), "Options", sf::Color::White);
    quitterButton = new Button(window, Maths::Vector2f(0.3f, 0.1f), "Quitter", sf::Color::White);

    // Positionnement des boutons
    jouerButton->GetShape()->setPosition(window->getSize().x / 2 - jouerButton->GetShape()->getSize().x / 2, 200);
    optionsButton->GetShape()->setPosition(window->getSize().x / 2 - optionsButton->GetShape()->getSize().x / 2, 350);
    quitterButton->GetShape()->setPosition(window->getSize().x / 2 - quitterButton->GetShape()->getSize().x / 2, 500);
}

void MainMenu::Render(sf::RenderWindow* _window)
{
    jouerButton->Render(_window);
    optionsButton->Render(_window);
    quitterButton->Render(_window);
}

int MainMenu::Update(sf::RenderWindow* _window)
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*_window));

    if (jouerButton->IsClicked(mousePos)) {
        return 1; // Code pour "Jouer"
    }
    else if (optionsButton->IsClicked(mousePos)) {
        return 2; // Code pour "Options"
    }
    else if (quitterButton->IsClicked(mousePos)) {
        return 3; // Code pour "Quitter"
    }

    return 0; // Aucun bouton cliqué
}

