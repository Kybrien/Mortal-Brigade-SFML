#include "Components/Light.h"

#include "SFML/Graphics/Shader.hpp"
#include "SFML/Graphics/Texture.hpp"

Light::Light()
{
	unshadowShader = new sf::Shader();
	lightOverShapeShader = new sf::Shader();
	unshadowShader->loadFromFile("../Assets/Shaders/unshadowShader.vert", "../Assets/Shaders/unshadowShader.frag");
	lightOverShapeShader->loadFromFile("../Assets/Shaders/lightOverShapeShader.vert", "../Assets/Shaders/lightOverShapeShader.frag");

	penumbraTexture = new sf::Texture();
	penumbraTexture->loadFromFile("../Assets/Shaders/penumbraTexture.png");
	penumbraTexture->setSmooth(true);

	pointLightTexture = new sf::Texture();
	pointLightTexture->loadFromFile("../Assets/Shaders/pointLightTexture.png");
}

Light::~Light()
{
	delete unshadowShader;
	delete lightOverShapeShader;
	delete penumbraTexture;
	delete pointLightTexture;
	delete ls;
	unshadowShader = nullptr;
	lightOverShapeShader = nullptr;
	penumbraTexture = nullptr;
	pointLightTexture = nullptr;
	ls = nullptr;
}

void Light::SetPoints(std::vector<sf::Vector2f*> _points) {
	lightShape->shape.setPointCount(_points.size());

	for (int j = 0; j < _points.size(); j++)
		lightShape->shape.setPoint(j, *_points[j]);

	lightShape->shape.setPosition(sf::Vector2f(0.f,0.f));
}

void Light::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	if (ls == nullptr) {
		ls->create(sf::FloatRect(0.0f, 0.0f, 1000.0f, 1000.0f), _window->getSize(), *penumbraTexture, *unshadowShader, *lightOverShapeShader);

		light->emissionSprite.setOrigin(0, 0);
		light->emissionSprite.setTexture(*pointLightTexture);
		light->emissionSprite.setColor(sf::Color::White);
		light->emissionSprite.setPosition(sf::Vector2f(0.f, 0.f));
		light->localCastCenter = sf::Vector2f(0.0f, 0.0f);

		ls->addLight(light);
	}

	const GameObject* owner = GetOwner();

	const Maths::Vector2<float> position = owner->GetPosition();
	light->emissionSprite.setPosition(sf::Vector2f(GetOwner()->GetPosition().x, GetOwner()->GetPosition().y));

	//_window->draw(*shape);
}
