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
#include "OpenLocker.h"
#include "Mine.h"
#include "MineElec.h"
#include "PathFinding.h"
#include "Teleporter.h"
#include "ChooseMap.h"
#include "FireSpot.h"

#include "Enemy.h"
#include "Lullaby.h"
#include "Red.h"

#include "Character.h"
#include "PauseComponent.h"
#include "TextRenderer.h"
#include "Death.h"

class DefaultScene final : public Scene
{
public:
	DefaultScene() : Scene("DefaultScene")
	{
		UsePlayerCamera(true);
		AssetModule::StopAll();

		AssetModule::PlaySound("welcome_back");
		AssetModule::SetSoundVolume("welcome_back", 30.f);

		GameObject* map = CreateMapGameObject("Map", "map_ship");

		GameObject* teleporter = CreateTeleporterGameObject("Teleporter", Maths::Vector2f(32 * 17.f, 32 * 12.5f));
    
		GameObject* player = CreatePlayerGameObject("Player", Maths::Vector2f(32*3.f, 32*6.f));

		GameObject* player_hud = CreatePlayerHudGameObject("PlayerHud");
		GameObject* quota = CreateQuotaGameObject("QuotaText");

		std::function<void()> openLocker = [this]() { Locker(); };

		GameObject* locker2 = CreateLockerGameObject(Maths::Vector2f(32 * 15.f, 32 * 4.f), openLocker);
		GameObject* locker5 = CreateLockerGameObject(Maths::Vector2f(32 * 19.f, 32 * 4.f), openLocker);

		SetPlayer(player);

		std::function<void()>* death = new std::function<void()>([this]() { Death(); });
		Character::SetFunc(death);
	}

	void MapSelection() {
		Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<ChooseMap>(true);
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

		if (Character::GetSpriteRenderer() == nullptr) {
			Character::SetSpriteRenderer(new SpriteRenderer);
			Character::SetInventory(new Inventory);
		}
		Character::SetMaxHealth(100);
		Character::SetMaxStamina(100);

		SpriteRenderer* sprite_renderer = Character::GetSpriteRenderer();
		game_object->AddComponent(sprite_renderer);
		sprite_renderer->LoadSprite("player");
		sprite_renderer->SetTextureSize(Maths::Vector2u(360, 300));
		sprite_renderer->SetScale(0.15f);
		sprite_renderer->SetAnimSpeed(0.5f);
		sprite_renderer->SetOffset(Maths::Vector2i(70, 70));

		SquareCollider* square_collider = game_object->CreateComponent<SquareCollider>();
		square_collider->SetWidth(32.f);
		square_collider->SetHeight(32.f);

		Inventory* inventory = Character::GetInventory();
		game_object->AddComponent(inventory);

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
		red_enemy_class->SetAttackSpeed(2.f);
		red_enemy_class->SetDamage(10);
		red_enemy_class->SetDetectionRange(150.f);

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

	//pb de sprite renderer ??
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
		sprite_renderer->LoadSprite("fire");
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


	GameObject* CreatePauseMenu(std::function<void()> _func) {
		GameObject* game_object = CreateGameObject("Pause");

		PauseComponent* resume = game_object->CreateComponent<PauseComponent>();
		resume->Execute(_func);

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
		
		if (Character::GetQuotaUI() == nullptr) {
			Character::SetQuotaUI(new TextRenderer);	
		}

		TextRenderer* quota = Character::GetQuotaUI();
		game_object->AddComponent(quota);
		quota->SetPosition(Maths::Vector2f(0.03f, 0.03f));
		quota->SetText("Quota:" + std::to_string(static_cast<int>(Character::GetInventory()->GetTotalMoney())) + "/" + std::to_string(static_cast<int>(Character::GetInventory()->GetQuotas())));
		quota->SetColor(sf::Color::White);

		return game_object;
	}

	GameObject* CreateLockerGameObject(const Maths::Vector2f _position , std::function<void()> _func)
	{
		GameObject* game_object = CreateGameObject("Locker");
		game_object->SetPosition(_position);

		OpenLocker* locker = game_object->CreateComponent<OpenLocker>();
		locker->SetFunc(_func);
		locker->SetCurrentScene(this);
		locker->SetMaxActivationDistance(50.f);

		return game_object;
	}

	void Locker() {
		Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<ChooseCharacter>(false);
		Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetMainScene("ChooseCharacterScene");
	}

	void Death() {
		Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<GameOver>();
	}

};
