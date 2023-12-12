#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Module.h"
#include "Modules/SceneModule.h"

class CameraModule final : public Module
{
public:
	void Start() override;
	void Update() override;
	void PostRender() override;

private:
	sf::RenderWindow* window = nullptr;
	sf::View* camera = nullptr;
	SceneModule* scene_module = nullptr;
};