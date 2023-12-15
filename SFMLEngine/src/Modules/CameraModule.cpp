#include <iostream>
#include "Modules/CameraModule.h"

#include "ModuleManager.h"
#include "Modules/WindowModule.h"
#include "Modules/SceneModule.h"
#include "Components/TileMap.h"
#include "Components/SquareCollider.h"

void CameraModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
	camera = new sf::View;
	scene_module = moduleManager->GetModule<SceneModule>();

	window->setView(*camera);
}

void CameraModule::Update()
{
	Module::Update();

	Scene* scene = scene_module->GetMainScene();

	if (scene->IsUsingPlayerCamera() == true) {
		GameObject* player = scene->GetPlayer();
		GameObject* map = scene->FindGameObject("Map");

		if (player && map) {
			SquareCollider* player_collider = player->GetComponent<SquareCollider>();

			camera->setSize(window->getSize().x / 5.f, window->getSize().y / 5.f);

			sf::Vector2f playerPosition = sf::Vector2f(player->GetPosition().x + player_collider->GetWidth() / 2, player->GetPosition().y + player_collider->GetHeight() / 2);

			sf::Vector2u windowSize(window->getSize().x, window->getSize().y);

			sf::Vector2f cameraSize = camera->getSize();

			float halfCameraWidth = cameraSize.x / 2.0f;
			float halfCameraHeight = cameraSize.y / 2.0f;

			if (playerPosition.x - halfCameraWidth < 0) {
				playerPosition.x = halfCameraWidth;
			}
			if (playerPosition.x + halfCameraWidth > map->GetComponent<TileMap>()->GetWidth()) {
				playerPosition.x = map->GetComponent<TileMap>()->GetWidth() - halfCameraWidth;
			}
			if (playerPosition.y - halfCameraHeight < 0) {
				playerPosition.y = halfCameraHeight;
			}
			if (playerPosition.y + halfCameraHeight > map->GetComponent<TileMap>()->GetHeight()) {
				playerPosition.y = map->GetComponent<TileMap>()->GetHeight() - halfCameraHeight;
			}

			camera->setCenter(playerPosition);
		}
	}
	else {
		camera->setSize(window->getSize().x, window->getSize().y);
		camera->setCenter(window->getSize().x / 2, window->getSize().y / 2);
	}

	window->setView(*camera);
}

void CameraModule::PostRender() {
	Module::PostRender();

	camera->setSize(window->getSize().x, window->getSize().y);
	camera->setCenter(window->getSize().x / 2, window->getSize().y / 2);

	window->setView(*camera);
}