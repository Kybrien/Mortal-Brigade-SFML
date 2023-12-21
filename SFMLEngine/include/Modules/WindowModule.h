#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Module.h"

class WindowModule final : public Module
{
public:
	sf::RenderWindow* GetWindow() const { return window; }

	void Init() override;
	void Start() override;
	void Update() override;
	void PreRender() override;
	void Render() override;
	void RenderGui() override;
	void PostRender() override;
	void Release() override;

	bool IsMousePressed() { return mouse_pressed; }

private:
	sf::RenderWindow* window = nullptr;
	bool mouse_pressed;
};