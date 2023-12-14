#pragma once
#include <SFML/Graphics/Text.hpp>
#include "RectangleShapeRenderer.h"

class Button : public RectangleShapeRenderer {
public:
    void Render(sf::RenderWindow* _window) override;
    bool IsMouseOver(sf::RenderWindow* _window);
    void Update(float _delta_time) override;
    void SetText(const std::string& _text);

private:
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Text buttonText;
};

