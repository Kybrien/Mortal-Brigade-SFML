#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Module.h"
#include "Modules/SceneModule.h"
#include "Modules/TimeModule.h"

class InputModule final : public Module
{
public:
	void Start() override;
	void Update() override;

	static bool IsKeyPressed(sf::Keyboard::Key key);

    static bool IsMouseButtonPressed(sf::Mouse::Button button);

private:
	sf::RenderWindow* window = nullptr;
	TimeModule* clock = nullptr;
	SceneModule* scene_module = nullptr;
};
