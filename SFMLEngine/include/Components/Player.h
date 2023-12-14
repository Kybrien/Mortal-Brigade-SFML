#pragma once

#include "Component.h"
#include "Maths/Vector2.h"
#include "Scene.h"

class Player : public Component
{
public:
	void Update(float _delta_time) override;

	void SetCurrentScene(Scene* _current_scene) { current_scene = _current_scene; }

private:
	Scene* current_scene = nullptr;
};
