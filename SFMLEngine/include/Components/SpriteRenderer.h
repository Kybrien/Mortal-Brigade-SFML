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

	void SetBegin(sf::Vector2i begin) { beginTexture = begin; }
	void SetEnd(sf::Vector2i end) { endTexture = end; }
	void SetDirection(sf::String _direction) { direction = _direction; }

	void IncrementCount() { count++; }

	void LoadSprite(std::string _name);
	void SetSprite(sf::Sprite* _sprite) { sprite = _sprite; }

	void SetScale(float _scale) { sprite->setScale(_scale, _scale); }

	void SetAnimSpeed(int _anim_speed) { anim_speed = _anim_speed; }

	void Update(float _delta_time) override;
	void Render(sf::RenderWindow* _window) override;

private:
	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;
	sf::Vector2i animation;
	int count = 0;
	int anim_speed = 10;
	int texture_size_x = 360;
	int texture_size_y = 300;
	sf::String direction = "";
	sf::String lastDirection = "";
	sf::Vector2i beginTexture = sf::Vector2i(0,0);
	sf::Vector2i endTexture = sf::Vector2i(0, 0);
};
