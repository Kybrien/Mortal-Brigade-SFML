#include <iostream>
#include "Modules/InputModule.h"

#include "ModuleManager.h"
#include "Modules/WindowModule.h"

#include "Components/SpriteRenderer.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
	clock = moduleManager->GetModule<TimeModule>();
	scene_module = moduleManager->GetModule<SceneModule>();
}

void InputModule::Update()
{
	Module::Update();

}

bool InputModule::IsKeyPressed(sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed(key);
}

bool InputModule::IsMouseButtonPressed(sf::Mouse::Button button)
{
    return sf::Mouse::isButtonPressed(button);
}