#pragma once
#include "RectangleShapeRenderer.h"
#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "SquareCollider.h"
#include "SpriteRenderer.h"
#include "Inventory.h"
#include "Light.h"
#include "ProximityPrompt.h"
#include "Collectable.h"

class DefaultScene final : public Scene
{
public:
	DefaultScene() : Scene("DefaultScene")
	{
		GameObject* map = CreateMapGameObject("Map", "map_ship");

		GameObject* door = CreateProximityPromptGameObject("Door1", Maths::Vector2f(32 * 25.f, 32 * 26.f), 20.f, "Test");

		GameObject* enemy = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 25.f, 32 * 25.f));

		GameObject* player = CreatePlayerGameObject("Player", Maths::Vector2f(32*25.f, 32*25.f));

		//GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Green);

	}

	GameObject* CreateMapGameObject(const std::string& _name, const std::string& map)
	{
		GameObject* game_object = CreateGameObject(_name);

		TileMap* tilemap = game_object->CreateComponent<TileMap>();
		tilemap->LoadMap(map, *this);

		return game_object;
	}

	GameObject* CreatePlayerGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		Player* player_component = game_object->CreateComponent<Player>();
		player_component->SetCurrentScene(this);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("Walk.png");
		sprite_renderer->SetTextureSize(Maths::Vector2u(360, 300));
		sprite_renderer->SetScale(0.15f);
		sprite_renderer->SetAnimSpeed(0.5f);
		sprite_renderer->SetOffset(Maths::Vector2i(70, 70));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(32.f);
		square_collider->SetHeight(32.f);

		Inventory* inventory = game_object->CreateComponent<Inventory>();

		Light* flashlight = game_object->CreateComponent<Light>();
		flashlight->SetShapes(GetLightColliders());

		return game_object;
	}

	GameObject* CreateREDMonsterGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("RED.png");
		sprite_renderer->SetTextureSize(Maths::Vector2u(48, 48));
		sprite_renderer->SetScale(0.8f);
		sprite_renderer->SetAnimSpeed(0.5f);
		sprite_renderer->SetAutoIncrement(true);
		sprite_renderer->SetBegin(sf::Vector2i(0, 1));
		sprite_renderer->SetEnd(sf::Vector2i(9, 1));
		sprite_renderer->SetOffset(Maths::Vector2i(5, 5));

		return game_object;
	}

	GameObject* CreateProximityPromptGameObject(const std::string& _name, const Maths::Vector2f _position, const float _max_activation_distance,const std::string _text)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		Collectable* proximity_prompt = game_object->CreateComponent<Collectable>();
		proximity_prompt->SetCurrentScene(this);
		proximity_prompt->SetMaxActivationDistance(_max_activation_distance);
		proximity_prompt->SetActionText(_text);

		return game_object;
	}
};
