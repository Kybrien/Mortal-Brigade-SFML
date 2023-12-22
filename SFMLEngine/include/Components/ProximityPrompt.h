#pragma once

#include "Component.h"
#include "Scene.h"
#include "Maths/Vector2.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class ProximityPrompt : public Component
{
public:
	ProximityPrompt();
	~ProximityPrompt();

	void SetActionText(std::string _action_text) { action_text = _action_text; }
	void SetMaxActivationDistance(float _max_activation_distance) { max_activation_distance = _max_activation_distance; }
	
	std::string GetActionText() { return action_text; }
	float GetMaxActivationDistance() { return max_activation_distance; }

	bool CanBePrompted();

	void SetCurrentScene(Scene* _current_scene) { current_scene = _current_scene; }

	virtual void Prompt() {};

	void Render(sf::RenderWindow* _window) override;
	void Update(float _delta_time) override;

protected:
	Scene* current_scene = nullptr;
	std::string action_text;
	float max_activation_distance;
	bool pressed = false;

	sf::Sprite* sprite;
};
