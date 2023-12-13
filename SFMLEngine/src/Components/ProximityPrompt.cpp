#include "Components/ProximityPrompt.h"
#include "Component.h"
#include <iostream>

#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Modules/InputModule.h"

ProximityPrompt::ProximityPrompt() {
	max_activation_distance = 0;

	texture = new sf::Texture();

	if (!texture->loadFromFile("../Assets/Images/ProximityPrompt.png"))
		std::cout << "Could not load ProximityPrompt.png";
	sprite = new sf::Sprite(*texture);

	sprite->setScale(0.04f, 0.04f);
}

bool ProximityPrompt::CanBePrompted() {
	GameObject* player = current_scene->FindGameObject("Player");

	if (player && (player->GetPosition() - GetOwner()->GetPosition()).Magnitude() < max_activation_distance) {
		return true;
	}
	return false;
}

void ProximityPrompt::Update(float _delta_time) {
	if (InputModule::IsKeyPressed(sf::Keyboard::E) && CanBePrompted()) {
		if (pressed == false) {
			pressed = true;
			std::cout << "Pressed !";
		}
	}
	else {
		pressed = false;
	}
}

void ProximityPrompt::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	GameObject* player = current_scene->FindGameObject("Player");

	if (player) {
		//std::cout << "player found";
		//std::cout << "Distance: " << (player->GetPosition() - GetOwner()->GetPosition()).Magnitude() << std::endl;
		if (CanBePrompted()) {
			//std::cout << "can prompt" << std::endl;
			const GameObject* owner = GetOwner();

			const Maths::Vector2<float> position = owner->GetPosition();
			sprite->setPosition(position.x, position.y);
			sprite->setRotation(owner->GetRotation());

			_window->draw(*sprite);
		}
	}

}