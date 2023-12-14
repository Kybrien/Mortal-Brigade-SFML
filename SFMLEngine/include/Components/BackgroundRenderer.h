#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp> 

class BackgroundRenderer : public Component {
public:
    BackgroundRenderer() : Component() {}

    void LoadTexture(const std::string& _texturePath);
    void Render(sf::RenderWindow* _window) override;
   

private:
    sf::Texture texture;
    sf::Sprite background;
};