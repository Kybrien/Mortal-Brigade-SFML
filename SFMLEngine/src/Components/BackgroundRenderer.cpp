#include "Components/BackgroundRenderer.h"

void BackgroundRenderer::LoadTexture(const std::string& _texturePath) {
    if (!texture.loadFromFile(_texturePath)) {
        // Gérer le cas où le chargement de la texture échoue
    }
    background.setTexture(texture);
}

void BackgroundRenderer::Render(sf::RenderWindow* _window) {
    background.setPosition(0, 0);
    // Dessiner le fond dans la fenêtre
    _window->draw(background);
}