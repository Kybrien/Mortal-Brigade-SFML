#pragma once
#include <functional>
#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include "RectangleShapeRenderer.h"

class Button : public RectangleShapeRenderer {
public:
    bool IsMouseOver(sf::RenderWindow* _window);
    void SetText(const std::string& _text);
    void OnClick(const std::function<void()> _func) { on_click = _func; }

    void SetBaseSize(const float _base_size) { base_size = _base_size; }
    void SetHoverSize(const float _hover_size) { hover_size = _hover_size; }
    void Animate(const bool _state) { animate = _state; }

    void Center(const bool _state);

    void Update(float _delta_time) override;
    void Render(sf::RenderWindow* _window) override;

private:
    float count = 0.f;
    float anim_speed = 0.005f;
    float base_size = 1.f;
    float hover_size = 1.2f;
    bool animate = false;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Text buttonText;
    bool clicked = false;
    std::function<void()> on_click;
};