#include "Components/ARendererComponent.h"
#include "Component.h"
#include <iostream>

void ARendererComponent::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	//std::cout << "ARendererComponent";
}
