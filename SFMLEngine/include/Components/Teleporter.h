#pragma once
#include "Scene.h"
#include <functional>

class Teleporter : public Component
{
public:
	void Update(float _delta_time) override;

	void SetScene(Scene* _scene) { current_scene = _scene; }

	void SetFunction(std::function<void()> _func) { func = _func; }
	//void Render(sf::RenderWindow* _window) override;
protected:
	Scene* current_scene = nullptr;
	bool teleported = false;
	std::function<void()> func;
};