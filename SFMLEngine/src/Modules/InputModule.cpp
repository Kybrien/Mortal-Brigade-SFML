#include <iostream>
#include "Modules/InputModule.h"

#include "ModuleManager.h"
#include "Modules/WindowModule.h"
#include "Modules/SceneModule.h"
#include "Modules/TimeModule.h"

#include "Components/SpriteRenderer.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();

	Scene* scene = moduleManager->GetModule<SceneModule>()->GetMainScene();
	TimeModule* clock = moduleManager->GetModule<TimeModule>();

	// IN-GAME INPUTS
	if (scene->GetName() == "DefaultScene") {
		GameObject* player = moduleManager->GetModule<SceneModule>()->GetMainScene()->FindGameObject("Player");
		if (player) {
			SpriteRenderer* playerSprite = player->GetComponent<SpriteRenderer>();
			SquareCollider* playerCollider = player->GetComponent<SquareCollider>();
			playerCollider->SetOldPosition(player->GetPosition());

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
				Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(0, -1) * clock->GetDeltaTime() * 50;

				player->SetPosition(newPos);
				playerSprite->SetDirection("UP");
				playerSprite->SetBegin(sf::Vector2i(4,3));
				playerSprite->SetEnd(sf::Vector2i(1, 5));
				playerSprite->IncrementCount();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(-1, 0) * clock->GetDeltaTime() * 50;

				player->SetPosition(newPos);
				playerSprite->SetDirection("LEFT");
				playerSprite->SetBegin(sf::Vector2i(6, 1));
				playerSprite->SetEnd(sf::Vector2i(3, 3));
				playerSprite->IncrementCount();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(0, 1) * clock->GetDeltaTime() * 50;

				player->SetPosition(newPos);
				playerSprite->SetDirection("DOWN");
				playerSprite->SetBegin(sf::Vector2i(0, 0));
				playerSprite->SetEnd(sf::Vector2i(5, 1));
				playerSprite->IncrementCount();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(1, 0) * clock->GetDeltaTime() * 50;

				player->SetPosition(newPos);
				playerSprite->SetDirection("RIGHT");
				playerSprite->SetBegin(sf::Vector2i(2, 5));
				playerSprite->SetEnd(sf::Vector2i(7, 6));
				playerSprite->IncrementCount();
			}

			for (int i = 0; i < scene->GetColliders().size(); i++) {
				if (SquareCollider::IsColliding(*playerCollider, *scene->GetColliders()[i])) {
					// Gérer les collisions horizontales et verticales séparément
					float deltaX = playerCollider->GetOwner()->GetPosition().x - scene->GetColliders()[i]->GetOwner()->GetPosition().x;
					float deltaY = playerCollider->GetOwner()->GetPosition().y - scene->GetColliders()[i]->GetOwner()->GetPosition().y;

					if (abs(deltaX) > abs(deltaY)) {
						// Collision horizontale
						playerCollider->MoveBack(0);
					}
					else {
						// Collision verticale
						playerCollider->MoveBack(1);
					}
				}
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