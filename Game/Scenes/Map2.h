#pragma once
#include "Scene.h"
//#include "TileMap.h"
#include "Player.h"
#include "Mine.h"
#include "Collectable.h"
#include "Inventory.h"
#include "Character.h"
#include "DefaultScene.h"
#include "QuotasReached.h"
#include "FireSpot.h"
#include "Red.h"

class DefaultScene;

class Map2 final : public Scene
{
public:
	Map2() : Scene("Map2Scene")
	{
		UsePlayerCamera(true);
		AssetModule::StopAll();

		AssetModule::PlaySound("player_spawn");

		AssetModule::Play("ambient");
		AssetModule::SetMusicVolume("ambient", 35.f);
		AssetModule::Loop("ambient",true);

		GameObject* map = CreateMapGameObject("Map", "map_2");

		GameObject* mine = CreateMineGameObject("Mine", Maths::Vector2f(32 * 46.f, 32 * 39.f));
		GameObject* mine2 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 55.f, 32 * 34.f));
		GameObject* mine3 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 48.f, 32 * 26.f));
		GameObject* mine4 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 46.f, 32 * 19.f));
		GameObject* mine5 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 48.f, 32 * 3.f));
		GameObject* mine6 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 26.f, 32 * 28.f));
		GameObject* mine7 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 38.f, 32 * 14.f));
		GameObject* mine8 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 26.f, 32 * 13.f));
		GameObject* mine9 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 19.f, 32 * 44.f));
		GameObject* mine10 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 13.f, 32 * 39.f));
		GameObject* mine11 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 18.f, 32 * 30.f));
		GameObject* mine12 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 2.f, 32 * 28.f));
		GameObject* mine13 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 9.f, 32 * 19.f));
		GameObject* mine14 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 15.f, 32 * 14.f));
		GameObject* mine15 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 3.f, 32 * 8.f));
		GameObject* mine16 = CreateMineGameObject("Mine", Maths::Vector2f(32 * 23.f, 32 * 6.1f));

		GameObject* fire = CreateFireGameObject("Fire", Maths::Vector2f(32 * 37.f, 32 * 47.f));
		GameObject* fire2 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 51.f, 32 * 47.f));
		GameObject* fire3 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 45.f, 32 * 39.f));
		GameObject* fire4 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 55.f, 32 * 34.f));
		GameObject* fire5 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 47.f, 32 * 24.f));
		GameObject* fire6 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 56.f, 32 * 15.f));
		GameObject* fire7 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 43.f, 32 * 15.f));
		GameObject* fire8 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 53.f, 32 * 9.f));
		GameObject* fire9 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 43.f, 32 * 4.f));
		GameObject* fire10 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 31.f, 32 * 8.f));
		GameObject* fire11 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 20.f, 32 * 3.f));
		GameObject* fire12 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 2.f, 32 * 10.f));
		GameObject* fire13 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 22.f, 32 * 12.f));
		GameObject* fire14 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 14.f, 32 * 22.f));
		GameObject* fire15 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 3.f, 32 * 21.f));
		GameObject* fire16 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 8.f, 32 * 29.f));
		GameObject* fire17 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 19.f, 32 * 32.f));
		GameObject* fire18 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 6.f, 32 * 39.f));
		GameObject* fire19 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 16.f, 32 * 49.f));
		GameObject* fire20 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 39.f, 32 * 39.f));
		GameObject* fire21 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 30.f, 32 * 33.f));
		GameObject* fire22 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 40.f, 32 * 20.f));
		GameObject* fire23 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 30.f, 32 * 19.f));
		GameObject* fire24 = CreateFireGameObject("Fire", Maths::Vector2f(32 * 26.f, 32 * 13.f));


		GameObject* collectable1 = CreateCollectableGameObject(Maths::Vector2f(32 * 49.f, 32 * 44.f));
		GameObject* collectable2 = CreateCollectableGameObject(Maths::Vector2f(32 * 51.f, 32 * 26.f));
		GameObject* collectable3 = CreateCollectableGameObject(Maths::Vector2f(32 * 40.f, 32 * 8.f));
		GameObject* collectable4 = CreateCollectableGameObject(Maths::Vector2f(32 * 57.f, 32 * 2.f));
		GameObject* collectable5 = CreateCollectableGameObject(Maths::Vector2f(32 * 33.f, 32 * 4.f));
		GameObject* collectable6 = CreateCollectableGameObject(Maths::Vector2f(32 * 41.f, 32 * 30.f));
		GameObject* collectable7 = CreateCollectableGameObject(Maths::Vector2f(32 * 25.f, 32 * 10.f));
		GameObject* collectable8 = CreateCollectableGameObject(Maths::Vector2f(32 * 8.f, 32 * 38.f));
		GameObject* collectable9 = CreateCollectableGameObject(Maths::Vector2f(32 * 20.f, 32 * 28.f));
		GameObject* collectable10 = CreateCollectableGameObject(Maths::Vector2f(32 * 11.f, 32 * 3.f));
		GameObject* collectable11 = CreateCollectableGameObject(Maths::Vector2f(32 * 5.f, 32 * 3.f));

		//Enemies
		GameObject* enemy = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 9.f, 32 * 5.f));
		GameObject* lullaby = CreateLullabyMonsterGameObject("Lullaby1", Maths::Vector2f(32 * 5.f, 32 * 20.f));
		GameObject* enemy2 = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 2.f, 32 * 34.f));
		GameObject* enemy3 = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 25.f, 32 * 19.f));
		GameObject* lullaby1 = CreateLullabyMonsterGameObject("Lullaby1", Maths::Vector2f(32 * 28.f, 32 * 33.f));
		GameObject* enemy5 = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 11.f, 32 * 36.f));
		GameObject* enemy6 = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 44.f, 32 * 15.f));
		GameObject* enemy7 = CreateREDMonsterGameObject("Enemy", Maths::Vector2f(32 * 54.f, 32 * 48.f));
		GameObject* lullaby2 = CreateLullabyMonsterGameObject("Lullaby1", Maths::Vector2f(32 * 29.f, 32 * 2.f));
		

		GameObject* teleporter = CreateTeleporterGameObject("Teleporter", Maths::Vector2f(32 * 35.f, 32 * 54.f));
		GameObject* player = CreatePlayerGameObject("Player", Maths::Vector2f(32 * 35.f, 32 * 53.f));


		GameObject* player_hud = CreatePlayerHudGameObject("PlayerHud");
		//GameObject* health_bar = CreateHealthBarGameObject("HealthBar");
		GameObject* quota = CreateQuotaGameObject("QuotaText");

		SetPlayer(player);
	}

	void MapSelection() {
		AssetModule::Stop("ambient");
		if (Character::GetMoonVisited()->size() == 3) {
			Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<QuotasNotReached>();
		}
		else if (Character::GetInventory()->GetTotalMoney() < Character::GetInventory()->GetQuotas()) {
			Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<ChooseMap>();
		}
		else {
			Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<QuotasReached>();
		}
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
	GameObject* CreateLullabyMonsterGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		sprite_renderer->LoadSprite("lullaby");
		sprite_renderer->SetTextureSize(Maths::Vector2u(64, 64));
		sprite_renderer->SetScale(0.5f);
		sprite_renderer->SetAnimSpeed(0.5f);
		sprite_renderer->SetAutoIncrement(true);
		sprite_renderer->SetBegin(sf::Vector2i(0, 0));
		sprite_renderer->SetEnd(sf::Vector2i(1, 0));
		sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

		Lullaby* enemy = game_object->CreateComponent<Lullaby>();
		enemy->SetScene(this);
		enemy->SetSpeed(40.f);
		enemy->SetMaxHealth(30);
		enemy->SetAttackSpeed(2.f);
		enemy->SetDamage(1000);
		enemy->SetDetectionRange(50.f);


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

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distrib(0, 3);
		int randomCollectable = distrib(gen);
		std::string name;
		float price = 0.f;
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

	GameObject* CreateFireGameObject(const std::string& _name, const Maths::Vector2f _position)
	{
		GameObject* game_object = CreateGameObject(_name);
		game_object->SetPosition(_position);
		FireSpot* firespot = game_object->CreateComponent<FireSpot>();
		firespot->SetScene(this);

		SpriteRenderer* sprite_renderer = game_object->CreateComponent<SpriteRenderer>();
		/*SpriteRenderer* sprite_renderer = GetOwner()->GetComponent<SpriteRenderer>();*/
		sprite_renderer->LoadSprite("fire");
		/*GetOwner()->SetPosition(GetOwner()->GetPosition() - Maths::Vector2f(64, 64));*/
		sprite_renderer->SetTextureSize(Maths::Vector2u(24, 32));
		sprite_renderer->SetScale(1.0f);
		sprite_renderer->SetAnimSpeed(1.0f);
		sprite_renderer->SetAutoIncrement(true);
		sprite_renderer->SetBegin(sf::Vector2i(0, 0));
		sprite_renderer->SetEnd(sf::Vector2i(7, 0));
		//sprite_renderer->SetOffset(Maths::Vector2i(0, 0));

		return game_object;
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
		/*sprite_renderer->SetOffset(Maths::Vector2i(5, 5));*/

		RED* red_enemy_class = game_object->CreateComponent<RED>();
		red_enemy_class->SetScene(this);
		red_enemy_class->SetSpeed(50.f);
		red_enemy_class->SetMaxHealth(30);
		red_enemy_class->SetAttackSpeed(20.f);
		red_enemy_class->SetDamage(10);
		red_enemy_class->SetDetectionRange(150.f);

		return game_object;
	}

	GameObject* CreatePlayerHudGameObject(const std::string& _name)
	{
		GameObject* game_object = CreateGameObject(_name);

		HealthBar* health_bar = game_object->CreateComponent<HealthBar>();
		TextRenderer* health = game_object->CreateComponent<TextRenderer>();
		health->SetPosition(Maths::Vector2f(0.03f, 0.79f));
		health->SetText("Health");

		StaminaBar* stamina_bar = game_object->CreateComponent<StaminaBar>();
		TextRenderer* stamina = game_object->CreateComponent<TextRenderer>();
		stamina->SetPosition(Maths::Vector2f(0.03f, 0.87f));
		stamina->SetText("Stamina");

		return game_object;
	}

	GameObject* CreateQuotaGameObject(const std::string& _name)
	{
		GameObject* game_object = CreateGameObject(_name);

		TextRenderer* quota = Character::GetQuotaUI();
		game_object->AddComponent(quota);


		return game_object;
	}
};

