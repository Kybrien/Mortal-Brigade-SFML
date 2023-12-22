#include <math.h>
#include "Modules/AssetModule.h"
#include "Components/HealthBar.h"
#include "Components/Character.h"

HealthBar::HealthBar() {
	background = new sf::Sprite();
	background->setTexture(*AssetModule::GetAsset("bg_health_bar"));
	background->setScale(0.4f, 0.4f);

	health_bar = new sf::Sprite();
	health_bar->setTexture(*AssetModule::GetAsset("health_bar"));
	health_bar->setScale(background->getScale());
}

HealthBar::~HealthBar() {
	delete background;
	delete health_bar;
	background = nullptr;
	health_bar = nullptr;
}

void HealthBar::RenderGui(sf::RenderWindow* _window) {
	Component::RenderGui(_window);

	const GameObject* owner = GetOwner();

	const Maths::Vector2f position = Maths::Vector2f(50, _window->getSize().y - _window->getSize().y * 0.18);
	background->setPosition(position.x, position.y);
	background->setRotation(owner->GetRotation());
	health_bar->setPosition(position.x, position.y);
	health_bar->setRotation(owner->GetRotation());

	float health_scale = static_cast<float>(Character::GetHealth()) / static_cast<float>(Character::GetMaxHealth());

	health_bar->setTextureRect(sf::IntRect(0, 0, round(1290 * health_scale), health_bar->getTextureRect().height));

	_window->draw(*background);
	_window->draw(*health_bar);
}