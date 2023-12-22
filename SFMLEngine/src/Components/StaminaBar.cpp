#include <math.h>
#include "Modules/AssetModule.h"
#include "Components/StaminaBar.h"
#include "Components/Character.h"

StaminaBar::StaminaBar() {
	background = new sf::Sprite();
	background->setTexture(*AssetModule::GetAsset("bg_health_bar"));
	background->setScale(0.4f, 0.4f);

	stamina_bar = new sf::Sprite();
	stamina_bar->setTexture(*AssetModule::GetAsset("stamina_bar"));
	stamina_bar->setScale(background->getScale());
}

StaminaBar::~StaminaBar() {
	delete background;
	delete stamina_bar;
	background = nullptr;
	stamina_bar = nullptr;
}

void StaminaBar::RenderGui(sf::RenderWindow* _window) {
	Component::RenderGui(_window);

	const GameObject* owner = GetOwner();

	const Maths::Vector2u position = Maths::Vector2u(50, _window->getSize().y - _window->getSize().y / 10);
	background->setPosition(position.x, position.y);
	background->setRotation(owner->GetRotation());
	stamina_bar->setPosition(position.x, position.y);
	stamina_bar->setRotation(owner->GetRotation());

	float stamina_scale = static_cast<float>(Character::GetStamina()) / static_cast<float>(Character::GetMaxStamina());

	stamina_bar->setTextureRect(sf::IntRect(0, 0, round(1290 * stamina_scale), stamina_bar->getTextureRect().height));

	_window->draw(*background);
	_window->draw(*stamina_bar);
}