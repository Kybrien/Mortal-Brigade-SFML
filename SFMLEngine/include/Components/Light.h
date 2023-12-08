#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <Lighting/LightSystem.h>

#include "ARendererComponent.h"

class Light : public Component
{
public:
	Light();
	~Light() override;

	void SetPoints(std::vector<sf::Vector2f*> _points);

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Shader* unshadowShader = nullptr;
	sf::Shader* lightOverShapeShader = nullptr;
	sf::Texture* penumbraTexture = nullptr;
	sf::Texture* pointLightTexture = nullptr;
	ltbl::LightSystem* ls = nullptr;
	std::shared_ptr<ltbl::LightPointEmission> light = std::make_shared<ltbl::LightPointEmission>();
	std::shared_ptr<ltbl::LightShape> lightShape = std::make_shared<ltbl::LightShape>();
};
