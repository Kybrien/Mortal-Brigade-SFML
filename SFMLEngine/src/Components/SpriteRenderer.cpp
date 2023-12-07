#include "Components/SpriteRenderer.h"
#include "SFML/Graphics/Texture.hpp"

SpriteRenderer::SpriteRenderer() {
	sprite = new sf::Sprite();
	texture = new sf::Texture();
	sprite->setTextureRect(sf::IntRect(animation.x * texture_size, animation.y * texture_size, texture_size, texture_size));
}

SpriteRenderer::~SpriteRenderer() {
	delete sprite;
	delete texture;
	sprite = nullptr;
	texture = nullptr;
}

void SpriteRenderer::LoadSprite(std::string _name) {
	texture = new sf::Texture;
		if (!texture->loadFromFile("../Assets/Sprites/" + _name)) {	
	}

	sprite->setTexture(*texture);
}

void SpriteRenderer::Update(float _delta_time) {
	if (count > anim_speed) {
		animation.x++;
		if (animation.x * texture_size >= texture->getSize().x) {
			animation.x = 0;
		}
		sprite->setTextureRect(sf::IntRect(animation.x * texture_size, animation.y * texture_size, texture_size, texture_size));
		count = 0;
	}
}

void SpriteRenderer::Render(sf::RenderWindow* _window)
{
	ARendererComponent::Render(_window);

	const GameObject* owner = GetOwner();

	const Maths::Vector2<float> position = owner->GetPosition();
	sprite->setPosition(position.x, position.y);
	sprite->setRotation(owner->GetRotation());

	_window->draw(*sprite);
}
