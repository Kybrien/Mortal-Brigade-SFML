#include "Components/Light.h"

#include "SFML/Graphics/Shader.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Engine.h"
#include "Modules/WindowModule.h"

#include <iostream>

Light::Light()
{
	sf::RenderWindow* window = Engine::GetInstance()->GetModuleManager()->GetModule<WindowModule>()->GetWindow();

	sf::RenderTexture normal_texture;
	sf::RenderTexture specular_texture_;

	ls = new ltbl::LightSystem(normal_texture, specular_texture_, false);
	ls->create({ -1000.f, -1000.f, 2000.f, 2000.f }, window->getSize());

	pointLightTexture = new sf::Texture();
	pointLightTexture->loadFromFile("../Assets/Shaders/pointLightTexture.png");
	pointLightTexture->setSmooth(true);

	light = new ltbl::LightPointEmission;
	light = ls->createLightPointEmission();
	light->setOrigin(sf::Vector2f(pointLightTexture->getSize().x * 0.5f, pointLightTexture->getSize().y * 0.5f));
	light->setTexture(*pointLightTexture);
	light->setScale(2.f, 2.f);
	light->setColor(sf::Color::White);
}

Light::~Light()
{
	delete pointLightTexture;
	delete ls;
	pointLightTexture = nullptr;
	ls = nullptr;
}

void Light::SetShapes(std::vector<SquareCollider*> _points) {
	for (int i = 0; i < _points.size(); i++) {
		sf::RectangleShape* blocker = new sf::RectangleShape;
		blocker->setSize({ _points[i]->GetWidth() + 0.1f, _points[i]->GetHeight() + 0.1f });
		blocker->setPosition({ _points[i]->GetOwner()->GetPosition().x, _points[i]->GetOwner()->GetPosition().y });
		blocker->setFillColor(sf::Color::Red);
		shapes.push_back(blocker);

		ls->createLightShape(*blocker);
	}
}

void Light::Render(sf::RenderWindow* _window)
{
	if (renderBool == true) {
		Component::Render(_window);

		//light->setPosition(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window), _window->getView()));
		light->setPosition(GetOwner()->GetPosition().x + GetOwner()->GetComponent<SquareCollider>()->GetWidth() / 2, GetOwner()->GetPosition().y + GetOwner()->GetComponent<SquareCollider>()->GetHeight() / 2);
		//std::cout << "X: " << light->getPosition().x << " Y:" << light->getPosition().y << std::endl;

		for (std::size_t i = 0; i < shapes.size(); i++)
		{
			//_window->draw(*shapes[i]);
		}

		ls->render(*_window);
	}
}
