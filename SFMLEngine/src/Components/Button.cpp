#include "Components/Button.h"
#include "Modules/InputModule.h"
#include<iostream>

void Button::Render(sf::RenderWindow* _window) {
    RectangleShapeRenderer::Render(_window);
    if (IsMouseOver(_window) && InputModule::IsMouseButtonPressed(sf::Mouse::Left) && (!clicked)) {
        clicked = true;
        on_click();
        std::cout << "Clicked" << std::endl;
    }
    _window->draw(*shape);

}

bool Button::IsMouseOver(sf::RenderWindow* _window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_window);
    sf::Vector2f buttonPosition = shape->getPosition();
    sf::Vector2f buttonSize = shape->getSize();

    return (mousePosition.x >= buttonPosition.x &&
        mousePosition.x <= buttonPosition.x + buttonSize.x &&
        mousePosition.y >= buttonPosition.y &&
        mousePosition.y <= buttonPosition.y + buttonSize.y);
}

void Button::Update(float _delta_time) {
    
}

void Button::SetText(const std::string& _text) {
    buttonText.setString(_text);
    //buttonText.setFont(/* Votre police de caractères */); // Assurez-vous de charger la police au préalable
    //buttonText.setCharacterSize(/* Taille de caractère */);
    //buttonText.setFillColor(/* Couleur du texte */);

//    // Positionner le texte au centre du bouton
//    sf::FloatRect textBounds = buttonText.getLocalBounds();
//    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
//    buttonText.setPosition(buttonShape.getPosition() + sf::Vector2f(buttonShape.getSize().x / 2.0f, buttonShape.getSize().y / 2.0f));
//
}