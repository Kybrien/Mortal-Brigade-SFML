#pragma once

#include "Component.h"
#include "Maths/Vector2.h"

class ProximityPrompt : public Component
{
public:
	void SetActionText(std::string _action_text) { action_text = _action_text; }
	void SetMaxActivationDistance(float _max_activation_distance) { max_activation_distance = _max_activation_distance; }
	
	std::string GetActionText() { return action_text; }
	float GetMaxActivationDistance() { return max_activation_distance; }

	void Render(sf::RenderWindow* _window) override;

protected:
	std::string action_text;
	float max_activation_distance;
};
