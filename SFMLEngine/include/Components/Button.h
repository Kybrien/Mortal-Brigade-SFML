#pragma once
#include <functional>
#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include "RectangleShapeRenderer.h"

class Button : public RectangleShapeRenderer {
public:
    void Render(sf::RenderWindow* _window) override;
    bool IsMouseOver(sf::RenderWindow* _window);
    void Update(float _delta_time) override;
    void SetText(const std::string& _text);
    void OnClick(std::function<void()> _func) { on_click = _func; }

private:
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Text buttonText;
    bool clicked = false;
    std::function<void()> on_click;
};