#pragma once

#include <iostream>
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

	void IncrementCount(float _delta_time) { count += 10 * _delta_time; }

	void LoadSprite(std::string _name);
	void SetSprite(sf::Sprite* _sprite) { sprite = _sprite; }

	void SetScale(float _scale) { sprite->setScale(_scale, _scale); }
	void SetTextureSize(Maths::Vector2u _texture_size) { texture_size_x = _texture_size.x; texture_size_y = _texture_size.y; }

	void SetAnimSpeed(float _anim_speed) { anim_speed = _anim_speed; }
	void SetOffset(const Maths::Vector2i _offset);
	void SetAutoIncrement(bool _state) { autoIncrement = _state; }

	void Update(float _delta_time) override;
	void Render(sf::RenderWindow* _window) override;

private:
	sf::Sprite* sprite = nullptr;
	sf::Texture* texture = nullptr;
	sf::Vector2i animation;
	float count = 0;
	float anim_speed = 1;
	unsigned int texture_size_x = 32;
	unsigned int texture_size_y = 32;
	sf::String direction = "";
	sf::String lastDirection = "";
	sf::Vector2i beginTexture = sf::Vector2i(0,0);
	sf::Vector2i endTexture = sf::Vector2i(0, 0);
	int offset_x = 0;
	int offset_y = 0;
	bool autoIncrement = false;
};
