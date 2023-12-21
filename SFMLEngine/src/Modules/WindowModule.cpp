#include "Modules/WindowModule.h"

#include <imgui-SFML.h>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine.h"
#include "Modules/InputModule.h"

void WindowModule::Init()
{
	Module::Init();

	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Mortal Brigade", sf::Style::Fullscreen);
	sf::Image logo;
	logo.loadFromFile("../Assets/Images/logo.png");
	window->setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
	window->setKeyRepeatEnabled(false);

	sf::Sprite loading_screen;
	sf::Texture texture;
	texture.loadFromFile("../Assets/Images/loading_screen.jpg");
	loading_screen.setTexture(texture);
	window->draw(loading_screen);
	window->display();
}

void WindowModule::Start()
{
	Module::Start();
}

void WindowModule::Update()
{
	Module::Update();

	sf::Event event;

	mouse_pressed = false;

	while (window->pollEvent(event))
	{
		//ImGui::SFML::ProcessEvent(*window, event);

		if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			mouse_pressed = true;
		}
		if (event.type == sf::Event::Closed)
		{
			Engine::GetInstance()->Quit();
		}
	}
}

void WindowModule::PreRender()
{
	Module::PreRender();

	window->clear(sf::Color::Black);
}

void WindowModule::Render()
{
	Module::Render();
}

void WindowModule::RenderGui()
{
	Module::RenderGui();
}

void WindowModule::PostRender()
{
	Module::PostRender();

	window->display();
}

void WindowModule::Release()
{
	Module::Release();

	window->close();
}
