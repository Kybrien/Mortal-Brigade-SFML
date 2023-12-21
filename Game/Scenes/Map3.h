#pragma once
#include "Scene.h"
#include "Player.h"
#include "mine.h"
#include "Collectable.h"
#include "Inventory.h"
#include "Character.h"
#include "Light.h"

class Map3 final : public Scene
{
public:
	Map3() : Scene("Map3Scene")
	{
		UsePlayerCamera(true);

		GameObject* map = CreateMapGameObject("Map", "map_3");

		GameObject* teleporter = CreateTeleporterGameObject("Teleporter", Maths::Vector2f(32 * 39.f, 32 * 1.f));
		GameObject* player = CreatePlayerGameObject("Player", Maths::Vector2f(32 * 39.f, 32 * 2.f));

		SetPlayer(player);
	}

	GameObject* CreateTeleporterGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(32.f);
		square_collider->SetHeight(32.f);

		RectangleShapeRenderer* shape_renderer = game_object->CreateComponent<RectangleShapeRenderer>();
		shape_renderer->SetSize(Maths::Vector2f(32.f, 32.f));
		shape_renderer->SetColor(sf::Color(0, 0, 0, 0));

		std::function<void()> map_select_func = [this]() { MapSelection(); };

		Teleporter* teleporter = game_object->CreateComponent<Teleporter>();
		teleporter->SetScene(this);
		teleporter->SetFunction(map_select_func);

		return game_object;
	}

	void MapSelection() {
		Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<ChooseMap>();
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
		player_component->SetCurrentScene(this);;

		SpriteRenderer* sprite_renderer = Character::GetSpriteRenderer();
		game_object->AddComponent(sprite_renderer);


		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(32.f);
		square_collider->SetHeight(32.f);

		Inventory* inventory = Character::GetInventory();
		game_object->AddComponent(inventory);

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

	GameObject* CreateCollectableGameObject(const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject("Collectable");
		game_object->SetPosition(_position);

		int randomCollectable = rand() % 4;
		std::string name;
		float price;
		switch (randomCollectable)
		{
		case 0:
			break;
		case 1:
			name = "coral";
			price = 10.f;
			break;
		case 2:
			name = "amethyst";
			price = 20.f;
			break;
		case 3:
			name = "ore";
			price = 30.f;
			break;
		default:
			break;
		}

		if (randomCollectable > 0) {
			SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
			sprite_renderer->LoadSprite(name);
			sprite_renderer->SetTextureSize(Maths::Vector2u(32, 32));
			sprite_renderer->SetScale(1.f);
			sprite_renderer->SetAnimSpeed(0.5f);
			//sprite_renderer->SetAutoIncrement(true);
			//sprite_renderer->SetBegin(sf::Vector2i(0, 0));
			//sprite_renderer->SetEnd(sf::Vector2i(0, 0));
			sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

			Collectable* collectable = game_object->CreateComponent<Collectable>();
			collectable->SetName(name);
			collectable->SetCurrentScene(this);
			collectable->SetMaxActivationDistance(25.f);
			collectable->SetActionText(name);
			collectable->SetPrice(price);
		}
		return game_object;
	}
};