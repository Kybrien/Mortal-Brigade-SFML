#include "Components/SpriteRenderer.h"
#include "SFML/Graphics/Texture.hpp"

SpriteRenderer::SpriteRenderer() {
	sprite = new sf::Sprite();
	texture = new sf::Texture();
}

SpriteRenderer::~SpriteRenderer() {
	delete sprite;
	sprite = nullptr;
}

void SpriteRenderer::LoadSprite(std::string _name) {
	texture = new sf::Texture;
		if (!texture->loadFromFile("../Assets/Sprites/" + _name)) {	
	}

	sprite->setTexture(*texture);
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
