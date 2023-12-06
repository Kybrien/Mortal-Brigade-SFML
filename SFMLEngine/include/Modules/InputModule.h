#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Module.h"

class InputModule final : public Module
{
public:
	void Start() override;
	void Update() override;

	static bool IsKeyPressed(sf::Keyboard::Key key);

    static bool IsMouseButtonPressed(sf::Mouse::Button button);

private:
	sf::RenderWindow* window = nullptr;
};
