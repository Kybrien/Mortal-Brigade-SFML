#pragma once
#include "Scene.h"
//#include "TileMap.h"
#include "Player.h"
#include "mine.h"
#include "Collectable.h"
#include "Inventory.h"
#include "Health.h"
#include "Light.h"
#include "Tilemap.h"

class Map1 final : public Scene
{
public:
	Map1() : Scene("Map1Scene")
	{
		UsePlayerCamera(true);

		GameObject* map = CreateMapGameObject("Map", "map_1");


		GameObject* mine = CreateMineGameObject("Mine", Maths::Vector2f(32 * 8.f, 32 * 25.f));

		GameObject* coral = CreateCollectableGameObject("Coral", Maths::Vector2f(32 * 6.f, 32 * 6.f), "Coral.png", 25.f, "Coral", 10.f);
		GameObject* coral2 = CreateCollectableGameObject("Coral", Maths::Vector2f(32 * 54.f, 32 * 29.f), "Coral.png", 25.f, "Coral", 10.f);
		GameObject* coral3 = CreateCollectableGameObject("Coral", Maths::Vector2f(32 * 50.f, 32 * 6.f), "Coral.png", 25.f, "Coral", 40.f);

		GameObject* ore = CreateCollectableGameObject("Ore", Maths::Vector2f(32 * 20.f, 32 * 12.f), "Ore.png", 40.f, "Ore", 10.f);
		GameObject* ore2 = CreateCollectableGameObject("Ore", Maths::Vector2f(32 * 26.f, 32 * 26.f), "Ore.png", 25.f, "Ore", 20.f);

		GameObject* amethyst = CreateCollectableGameObject("Amethyst", Maths::Vector2f(32 * 39.f, 32 * 14.f), "Amethyst.png", 25.f, "Amethyst", 30.f);


		GameObject* player = CreatePlayerGameObject("Player", Maths::Vector2f(32 * 9.f, 32 * 29.f));

		SetPlayer(player);
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

		Health* player_health = game_object->CreateComponent<Health>();

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

	GameObject* CreateMineGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);
		Mine* mine = game_object->CreateComponent<Mine>();
		mine->SetScene(this);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("Mine.png");
		sprite_renderer->SetTextureSize(Maths::Vector2u(360, 360));
		sprite_renderer->SetScale(0.05f);
		sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

		return game_object;
	}

	GameObject* CreateCollectableGameObject(const std::string& _name, const Maths::Vector2f _position, std::string _texture, const float _max_activation_distance, const std::string _text, float _price)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite(_texture);
		sprite_renderer->SetTextureSize(Maths::Vector2u(32, 32));
		sprite_renderer->SetScale(1.f);
		sprite_renderer->SetAnimSpeed(0.5f);
		//sprite_renderer->SetAutoIncrement(true);
		//sprite_renderer->SetBegin(sf::Vector2i(0, 0));
		//sprite_renderer->SetEnd(sf::Vector2i(0, 0));
		sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

		Collectable* collectable = game_object->CreateComponent<Collectable>();
		collectable->SetCurrentScene(this);
		collectable->SetMaxActivationDistance(_max_activation_distance);
		collectable->SetActionText(_text);
		collectable->SetPrice(_price);

		return game_object;
	}
};