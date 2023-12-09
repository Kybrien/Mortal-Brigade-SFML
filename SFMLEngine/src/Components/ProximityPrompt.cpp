#include "Components/ProximityPrompt.h"
#include "Component.h"
#include <iostream>

#include "Engine.h"
#include "Modules/SceneModule.h"

void ProximityPrompt::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	Scene* scene = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->GetMainScene();

	if (scene->FindGameObject("Player")) {
		//std::cout << "player found";
	}
}