#include <iostream>
#include "Modules/InputModule.h"

#include "ModuleManager.h"
#include "Modules/WindowModule.h"
#include "Modules/SceneModule.h"
#include "Modules/TimeModule.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();

	TimeModule* clock = moduleManager->GetModule<TimeModule>();

	// IN-GAME INPUTS
	if (moduleManager->GetModule<SceneModule>()->GetMainScene()->GetName() == "DefaultScene") {
		GameObject* player = moduleManager->GetModule<SceneModule>()->GetMainScene()->FindGameObject("Player");
		if (player) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				player->SetPosition(player->GetPosition() + Maths::Vector2f(0, -1) * clock->GetDeltaTime() * 50);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				player->SetPosition(player->GetPosition() + Maths::Vector2f(-1, 0) * clock->GetDeltaTime() * 50);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				player->SetPosition(player->GetPosition() + Maths::Vector2f(0, 1) * clock->GetDeltaTime() * 50);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				player->SetPosition(player->GetPosition() + Maths::Vector2f(1, 0) * clock->GetDeltaTime() * 50);
			}
		}
	}
}

bool InputModule::IsKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool InputModule::IsMouseButtonPressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}