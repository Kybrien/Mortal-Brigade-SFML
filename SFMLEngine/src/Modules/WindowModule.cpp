#include "Modules/WindowModule.h"

#include <imgui-SFML.h>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine.h"
#include "Modules/InputModule.h"

void WindowModule::Init()
{
	Module::Init();

	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFML Engine", sf::Style::Fullscreen);
	sf::Image logo;
	logo.loadFromFile("../Assets/logo.png");
	window->setIcon(logo.getSize().x, logo.getSize().y, logo.getPixelsPtr());
}

void WindowModule::Start()
{
	Module::Start();
}

void WindowModule::Update()
{
	Module::Update();

	sf::Event event;
	while (window->pollEvent(event))
	{
		//ImGui::SFML::ProcessEvent(*window, event);

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
