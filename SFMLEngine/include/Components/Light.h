#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <Lighting/LightSystem.hpp>

#include "ARendererComponent.h"
#include "Components/SquareCollider.h"

class Light : public Component
{
public:
	Light();
	~Light() override;

	void SetShapes(std::vector<SquareCollider*> _shapes);

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Shader* unshadowShader = nullptr;
	sf::Shader* lightOverShapeShader = nullptr;
	sf::Texture* penumbraTexture = nullptr;
	sf::Texture* pointLightTexture = nullptr;
	ltbl::LightSystem* ls = nullptr;
	ltbl::LightPointEmission* light = nullptr;
	std::vector<sf::RectangleShape*> shapes;
	std::shared_ptr<ltbl::LightShape> lightShape = std::make_shared<ltbl::LightShape>();
};
