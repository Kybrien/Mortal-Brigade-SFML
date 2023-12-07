#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "ARendererComponent.h"

class SpriteRenderer : public ARendererComponent
{
public:
	SpriteRenderer();
	~SpriteRenderer() override;

	sf::Vector2i GetAnimation() { return animation; }
	void SetAnimation(int y) { animation.y = y; }

	void IncrementCount() { count++; }

	void LoadSprite(std::string _name);
	void SetSprite(sf::Sprite* _sprite) { sprite = _sprite; }

	void SetScale(float _scale) { sprite->setScale(_scale, _scale); }
	void SetAnimSpeed(int _anim_speed) { anim_speed = _anim_speed; }

	void Update(float _delta_time) override;
	void Render(sf::RenderWindow* _window) override;

private:
	enum Direction { DOWN, UP, RIGHT, LEFT };
	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;
	sf::Vector2i animation = sf::Vector2i(1, DOWN);
	int count = 0;
	int anim_speed = 10;
	int texture_size = 32;
};
