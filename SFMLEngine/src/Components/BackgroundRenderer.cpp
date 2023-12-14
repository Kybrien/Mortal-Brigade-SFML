#include "Components/BackgroundRenderer.h"

void BackgroundRenderer::LoadTexture(const std::string& _texturePath) {
    if (!texture.loadFromFile(_texturePath)) {
        // Gérer le cas où le chargement de la texture échoue
    }
    background.setTexture(texture);
}

void BackgroundRenderer::Render(sf::RenderWindow* _window) {
    // Obtenir la taille de la fenêtre
    sf::Vector2u windowSize = _window->getSize();

    // Mettre à jour la taille du fond pour correspondre à la taille de la fenêtre
    sf::Vector2f newScale(static_cast<float>(windowSize.x) / background.getTexture()->getSize().x,
        static_cast<float>(windowSize.y) / background.getTexture()->getSize().y);
    background.setScale(newScale);

    // Dessiner le fond dans la fenêtre
    _window->draw(background);
}
