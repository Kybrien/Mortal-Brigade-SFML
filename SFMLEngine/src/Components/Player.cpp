#include "Components/Player.h"
#include "Components/Character.h"
#include "Components/SpriteRenderer.h"
#include "Components/SquareCollider.h"
#include "Components/Light.h"
#include "Modules/InputModule.h"

void Player::Update(float _delta_time)
{
	Component::Update(_delta_time);

	GameObject* player = GetOwner();
	bool moving = false;
	SpriteRenderer* playerSprite = player->GetComponent<SpriteRenderer>();
	SquareCollider* playerCollider = player->GetComponent<SquareCollider>();

	int speed = 50;
	bool sprinting = false;
	int sprint_speed = 70;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && Character::GetSprint() == true) {
		speed = sprint_speed;
		sprinting = true;
	}


	if (current_scene->GetName() == "Map1Scene" || current_scene->GetName() == "Map2Scene" || current_scene->GetName() == "Map3Scene") {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
			current_scene->UsePlayerCamera(false);
			current_scene->GetPlayer()->GetComponent<Light>()->SetRender(false);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
			current_scene->UsePlayerCamera(true);
			current_scene->GetPlayer()->GetComponent<Light>()->SetRender(true);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(0, -1) * _delta_time * speed;

		player->SetPosition(newPos);
		playerSprite->SetDirection("UP");
		playerSprite->SetBegin(sf::Vector2i(4, 3));
		playerSprite->SetEnd(sf::Vector2i(1, 5));
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(-1, 0) * _delta_time * speed;

		player->SetPosition(newPos);
		playerSprite->SetDirection("LEFT");
		playerSprite->SetBegin(sf::Vector2i(6, 1));
		playerSprite->SetEnd(sf::Vector2i(3, 3));
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(0, 1) * _delta_time * speed;

		player->SetPosition(newPos);
		playerSprite->SetDirection("DOWN");
		playerSprite->SetBegin(sf::Vector2i(0, 0));
		playerSprite->SetEnd(sf::Vector2i(5, 1));
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		Maths::Vector2f newPos = player->GetPosition() + Maths::Vector2f(1, 0) * _delta_time * speed;

		player->SetPosition(newPos);
		playerSprite->SetDirection("RIGHT");
		playerSprite->SetBegin(sf::Vector2i(2, 5));
		playerSprite->SetEnd(sf::Vector2i(7, 6));
		moving = true;
	}

	if (moving) {
		playerSprite->IncrementCount(_delta_time);

		if (sprinting) {
			Character::SetStamina(_delta_time * -20.f);
		}
	}
	if (moving || (!moving && sprinting) || (!moving && !sprinting))
	{
		Character::SetStamina(_delta_time * 10.f);
	}

	for (int i = 0; i < current_scene->GetColliders().size(); i++) {
		if (SquareCollider::IsColliding(*playerCollider, *current_scene->GetColliders()[i])) {
			// Gérer les collisions horizontales et verticales séparément
			float deltaX = playerCollider->GetOwner()->GetPosition().x - current_scene->GetColliders()[i]->GetOwner()->GetPosition().x;
			float deltaY = playerCollider->GetOwner()->GetPosition().y - current_scene->GetColliders()[i]->GetOwner()->GetPosition().y;


			if (abs(deltaX) > abs(deltaY)) {
				// Collision horizontale
				//playerCollider->MoveBack(0);
				if (deltaX > 0) {
					// Le joueur est à droite du mur, ajustez la position vers la gauche
					player->SetPosition(Maths::Vector2f(current_scene->GetColliders()[i]->GetOwner()->GetPosition().x + playerCollider->GetWidth(), player->GetPosition().y));
				}
				else {
					// Le joueur est à gauche du mur, ajustez la position vers la droite
					player->SetPosition(Maths::Vector2f(current_scene->GetColliders()[i]->GetOwner()->GetPosition().x - playerCollider->GetWidth(), player->GetPosition().y));
				}
			}
			if (abs(deltaX) < abs(deltaY)) {
				// Collision verticale
				//playerCollider->MoveBack(1);
				if (deltaY > 0) {
					// Le joueur est en dessous du mur, ajustez la position vers le haut
					player->SetPosition(Maths::Vector2f(player->GetPosition().x, current_scene->GetColliders()[i]->GetOwner()->GetPosition().y + playerCollider->GetHeight()));
				}
				else {
					// Le joueur est au-dessus du mur, ajustez la position vers le bas
					player->SetPosition(Maths::Vector2f(player->GetPosition().x, current_scene->GetColliders()[i]->GetOwner()->GetPosition().y - playerCollider->GetHeight()));
				}
			}
		}
	}
}