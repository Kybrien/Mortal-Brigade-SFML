#pragma once
#include "RectangleShapeRenderer.h"
#include "Scene.h"
#include "TileMap.h"
#include "SquareCollider.h"
#include "SpriteRenderer.h"

class DefaultScene final : public Scene
{
public:
	DefaultScene() : Scene("DefaultScene")
	{
		GameObject* map = CreateMapGameObject("Map", "Lvl01");

		GameObject* player = CreateDummyGameObject("Player", 200.f, sf::Color::Red);

		GameObject* enemy = CreateDummyGameObject("Enemy", 400.f, sf::Color::Blue);
		GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Green);

		//TileMap* map = new TileMap;
		//map->LoadMap("Lvl01", *this);
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

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(20.f);
		square_collider->SetHeight(20.f);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		//sprite_renderer->LoadSprite("Test.png");

		//RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		//shape_renderer->SetColor(_color);
		//shape_renderer->SetSize(Maths::Vector2f(200.f, 200.f));

		return game_object;
	}
};
