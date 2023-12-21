#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Component.h"

class HealthBar : public Component {
public:
	HealthBar();
	~HealthBar();

	void SetPosition(const Maths::Vector2f& _position) { position = _position; }

	void RenderGui(sf::RenderWindow* _window) override;

private:
	Maths::Vector2f position;
	sf::Sprite* background = nullptr;
	sf::Sprite* health_bar = nullptr;
};