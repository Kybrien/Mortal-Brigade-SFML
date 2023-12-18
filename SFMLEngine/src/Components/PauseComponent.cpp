#include "Components/PauseComponent.h"
#include "Modules/InputModule.h"
#include "Engine.h"

void PauseComponent::Update(float _delta_time) {
	if (InputModule::IsKeyPressed(sf::Keyboard::Escape)) {
		if (IsPressed == false) {
			IsPressed = true;
			execute();
		}
	}
}