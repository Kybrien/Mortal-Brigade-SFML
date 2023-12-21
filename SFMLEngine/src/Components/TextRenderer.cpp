#include "Modules/AssetModule.h"
#include "Components/TextRenderer.h"

TextRenderer::TextRenderer() {
	text = new sf::Text();
	text->setFont(*AssetModule::GetFont("vcr_osd"));
}

TextRenderer::~TextRenderer() {
	delete text;
	text = nullptr;
}

void TextRenderer::RenderGui(sf::RenderWindow* _window)
{
	sf::Vector2f scalar_pos = sf::Vector2f(_window->getSize().x * position.x, _window->getSize().y * position.y);
	text->setPosition(scalar_pos);

	_window->draw(*text);
}

void TextRenderer::Center(const bool _state) {
	sf::FloatRect textRect = text->getLocalBounds();
	if (_state) {
		text->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	}
	else
	{
		text->setOrigin(0.f, 0.f);
	}
}