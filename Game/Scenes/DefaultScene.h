#pragma once
#include "RectangleShapeRenderer.h"
#include "Scene.h"
#include "TileMap.h"
#include "SquareCollider.h"
#include "SpriteRenderer.h"
#include "Light.h"

class DefaultScene final : public Scene
{
public:
	DefaultScene() : Scene("DefaultScene")
	{
		GameObject* map = CreateMapGameObject("Map", "map_ship");

		GameObject* player = CreateDummyGameObject("Player", 32*25.f, sf::Color::Red);

		GameObject* enemy = CreateDummyGameObject("Enemy", 400.f, sf::Color::Blue);
		GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Green);
	}

	GameObject* CreateMapGameObject(const std::string& _name, const std::string& map)
	{
		GameObject* game_object = CreateGameObject(_name);

		TileMap* tilemap = game_object->CreateComponent<TileMap>();
		tilemap->LoadMap(map, *this);

		return game_object;
	}

	GameObject* CreateDummyGameObject(const std::string& _name, const float _position, const sf::Color _color)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(Maths::Vector2f(_position, _position));

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("Walk.png");
		sprite_renderer->SetScale(0.15f);
		sprite_renderer->SetAnimSpeed(35);

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(32.f);
		square_collider->SetHeight(32.f);

		//Light* flashlight = game_object->CreateComponent<Light>();

		return game_object;
	}
};
