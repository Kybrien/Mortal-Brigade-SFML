#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Maths/Vector2.h"
#include "Component.h"

class TextRenderer : public Component
{
public:
	TextRenderer();
	~TextRenderer();

	unsigned int GetSize() const { return text->getCharacterSize(); }
	void SetPosition(const Maths::Vector2f& _position) { position = _position; }
	void SetSize(const int _size) { text->setCharacterSize(_size); }
	void SetText(const std::string _text) { text->setString(_text); }
	void SetColor(const sf::Color _color) { text->setFillColor(_color); }
	void Center(const bool _state);

	void RenderGui(sf::RenderWindow* _window) override;

protected:
	sf::Text* text = nullptr;
	Maths::Vector2f position;
};
