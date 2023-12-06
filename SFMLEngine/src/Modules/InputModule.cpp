#include <iostream>
#include "Modules/InputModule.h"

#include "ModuleManager.h"
#include "Modules/WindowModule.h"

void InputModule::Start()
{
	Module::Start();

	window = moduleManager->GetModule<WindowModule>()->GetWindow();
}

void InputModule::Update()
{
	Module::Update();

	if (IsKeyPressed(sf::Keyboard::Left)) {
		std::cout << "left";
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