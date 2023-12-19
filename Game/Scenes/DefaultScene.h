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
#include "Mine.h"
#include "MineElec.h"
#include "Health.h"
#include "PathFinding.h"
#include "Teleporter.h"
#include "ChooseMap.h"
#include "FireSpot.h"

class DefaultScene final : public Scene
{
public:
	DefaultScene() : Scene("DefaultScene")
	{
		UsePlayerCamera(true);

		GameObject* map = CreateMapGameObject("Map", "map_ship");

		//GameObject* door = CreateProximityPromptGameObject("Door1", Maths::Vector2f(32 * 25.f, 32 * 26.f), 20.f, "Test");

		GameObject* enemy = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 2.f, 32 * 5.f)); 


		GameObject* teleporter = CreateTeleporterGameObject("Teleporter", Maths::Vector2f(32 * 17.f, 32 * 12.5f));

		GameObject* FireSpot = CreateFireGameObject("FireSpot", Maths::Vector2f(32 * 28.f, 32 * 26.f));
    
		GameObject* player = CreatePlayerGameObject("Player", Maths::Vector2f(32*3.f, 32*6.f));

		SetPlayer(player);
		//GameObject* teleporter = CreateTeleporterGameObject("Teleporter", Maths::Vector2f(32 * 28.f, 32 * 25.f));

		//GameObject* enemy2 = CreateDummyGameObject("Enemy2", 0.f, sf::Color::Green);

	}

	void MapSelection() {
		Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<ChooseMap>();
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
		shape_renderer->SetColor(sf::Color(0,0,0,0));

		std::function<void()> map_select_func = [this]() { MapSelection(); };

		Teleporter* teleporter = game_object->CreateComponent<Teleporter>();
		teleporter->SetScene(this);
		teleporter->SetFunction(map_select_func);

		return game_object;
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

	GameObject* CreateREDMonsterGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("red");
		sprite_renderer->SetTextureSize(Maths::Vector2u(48, 48));
		sprite_renderer->SetScale(0.8f);
		sprite_renderer->SetAnimSpeed(0.5f);
		sprite_renderer->SetAutoIncrement(true);
		sprite_renderer->SetBegin(sf::Vector2i(0, 1));
		sprite_renderer->SetEnd(sf::Vector2i(9, 1));
		sprite_renderer->SetOffset(Maths::Vector2i(5, 5));

		PathFinding* ai = game_object->CreateComponent<PathFinding>();
		ai->FindPath(GetColliders(), _position, Maths::Vector2f(32 * 15.f, 32 * 10.f));


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

	GameObject* CreateMineElecGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);
		MineElec* mine_elec = game_object->CreateComponent<MineElec>();
		mine_elec->SetScene(this);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("mine_elec");
		sprite_renderer->SetTextureSize(Maths::Vector2u(360, 360));
		sprite_renderer->SetScale(0.05f);
		sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

		return game_object;
	}

	GameObject* CreateFireGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);
		FireSpot* firespot = game_object->CreateComponent<FireSpot>();
		firespot->SetScene(this);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("Fire.png");
		sprite_renderer->SetTextureSize(Maths::Vector2u(24, 32));
		sprite_renderer->SetScale(1.0f);
		sprite_renderer->SetAnimSpeed(1.0f);
		sprite_renderer->SetAutoIncrement(true);
		sprite_renderer->SetBegin(sf::Vector2i(0, 0));
		sprite_renderer->SetEnd(sf::Vector2i(7, 0));
		//sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

		return game_object;
	}

	GameObject* CreateProximityPromptGameObject(const std::string& _name, const Maths::Vector2f _position, const float _max_activation_distance,const std::string _text)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		ProximityPrompt* proximity_prompt = game_object->CreateComponent<ProximityPrompt>();
		proximity_prompt->SetCurrentScene(this);
		proximity_prompt->SetMaxActivationDistance(_max_activation_distance);
		proximity_prompt->SetActionText(_text);

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

		return game_object;
	}
};
