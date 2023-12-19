#pragma once
#include "Scene.h"
//#include "TileMap.h"
#include "Player.h"
#include "mine.h"
#include "Collectable.h"
#include "Inventory.h"

class Map1 final : public Scene 
{
public:
	Map1() : Scene("Map1Scene")
	{
		UsePlayerCamera(true);

		GameObject* map = CreateMapGameObject("Map", "map_1");


		GameObject* mine = CreateMineGameObject("Mine", Maths::Vector2f(32 * 8.f, 32 * 25.f));
		GameObject* mine1 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 14.f, 32 * 16.f));
		GameObject* mine2 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 42.f, 32 * 13.f));
		GameObject* mine3 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 52.f, 32 * 9.f));
		GameObject* mine4 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 37.f, 32 * 19.f));
		GameObject* mine5 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 24.f, 32 * 25.f));
		GameObject* mine6 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 20.f, 32 * 27.f));
		GameObject* mine7 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 49.f, 32 * 24.f));
		GameObject* mine8 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 43.f, 32 * 31.f));
		GameObject* mine9 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 48.f, 32 * 43.f));
		GameObject* mine10 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 41.f, 32 * 53.f));
		GameObject* mine11 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 29.f, 32 * 56.f));
		GameObject* mine12 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 14.f, 32 * 43.f));
		GameObject* mine13 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 9.f, 32 * 46.f));


		GameObject* coral = CreateCollectableGameObject("Coral", Maths::Vector2f(32 * 6.f, 32 * 6.f), "coral", 25.f, "Coral", 10.f);
		GameObject* coral2 = CreateCollectableGameObject("Coral2", Maths::Vector2f(32 * 19.f, 32 * 10.f), "coral", 25.f, "Coral", 10.f);
		GameObject* amethyst = CreateCollectableGameObject("Amethyst", Maths::Vector2f(32 * 38.f, 32 * 4.f), "amethyst", 25.f, "Amethyst", 20.f);
		GameObject* coral3 = CreateCollectableGameObject("Coral3", Maths::Vector2f(32 * 45.f, 32 * 7.f), "coral", 25.f, "Coral", 10.f);
		GameObject* amethyst2 = CreateCollectableGameObject("Amethyst", Maths::Vector2f(32 * 36.f, 32 * 14.f), "amethyst", 25.f, "Amethyst", 20.f);
		GameObject* coral4 = CreateCollectableGameObject("Coral3", Maths::Vector2f(32 * 53.f, 32 * 39.f), "coral", 25.f, "Coral", 10.f);
		GameObject* coral5 = CreateCollectableGameObject("Coral3", Maths::Vector2f(32 * 52.f, 32 * 26.f), "coral", 25.f, "Coral", 10.f);
		GameObject* amethyst3 = CreateCollectableGameObject("Amethyst", Maths::Vector2f(33 * 36.f, 32 * 35.f), "amethyst", 25.f, "Amethyst", 20.f);
		GameObject* ore = CreateCollectableGameObject("Ore", Maths::Vector2f(32 * 23.f, 32 * 54.f), "ore", 40.f, "Ore", 10.f);
		GameObject* coral6 = CreateCollectableGameObject("Coral", Maths::Vector2f(32 * 14.f, 32 * 37.f), "coral", 25.f, "Coral", 10.f);
		GameObject* ore2 = CreateCollectableGameObject("Ore", Maths::Vector2f(32 * 14.f, 32 * 37.f), "ore", 40.f, "Ore", 10.f);





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
		sprite_renderer->LoadSprite("player");
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
		sprite_renderer->LoadSprite("mine");
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