#pragma once
#include "Scene.h"
#include <functional>
#include "BackgroundRenderer.h"
#include "Button.h" 
#include "SpriteRenderer.h"
#include "Engine.h"
#include "MenuScene.h"

class MenuScene;

class ChooseCharacter : public Scene {
public:
    ChooseCharacter() : Scene("ChooseCharacterScene") {
        GameObject* background = CreateBackgroundGameObject("MapSelectionBackground", "map_selection_background");

        std::function<void()> selectPink = [this]() { SetColor("Pink"); };
        std::function<void()> selectBlue = [this]() { SetColor("Blue"); };
        std::function<void()> selectGreen = [this]() { SetColor("Green"); };
        std::function<void()> selectYellow = [this]() { SetColor("Yellow"); };
        std::function<void()> selectRed = [this]() { SetColor("Red"); };

        GameObject* CharacterButtonPink = CreateCharacterButton("CharacterButtonPink", 600.f, 75.f, "playerButtonPink", selectPink);
        GameObject* CharacterButtonBlue = CreateCharacterButton("CharacterButtonBlue", 900.f, 75.f, "playerButtonBlue", selectBlue);
        GameObject* CharacterButtonGreen = CreateCharacterButton("CharacterButtonGreen", 600.f, 400.f, "playerButtonGreen", selectGreen);
        GameObject* CharacterButtonYellow = CreateCharacterButton("CharacterButtonYellow", 900.f, 400.f, "playerButtonYellow", selectYellow);
        GameObject* CharacterButtonRed = CreateCharacterButton("CharacterButtonRed", 750.f, 700.f, "playerButtonRed", selectRed);
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texture_path) {
        GameObject* game_object = CreateGameObject(_name);
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texture_path);
        return game_object;
    }

    GameObject* CreateCharacterButton(const std::string& _name, float _x, float _y, const std::string& _texture_name, std::function<void()> func) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton pour choisir une carte
        Button* button = game_object->CreateComponent<Button>();
        button->SetSize(Maths::Vector2f(400.f, 400.f));
        button->SetColor(sf::Color(0, 0, 0, 0));
        button->OnClick(func);
        button->SetBaseSize(3.f);
        button->SetHoverSize(3.5f);
        SpriteRenderer* sprite = game_object->CreateComponent<SpriteRenderer>();
        sprite->LoadSprite(_texture_name);
        sprite->SetTextureSize(Maths::Vector2u(360, 300));
        sprite->SetScale(2.f);
        sprite->SetAnimSpeed(1.f);
        sprite->SetOffset(Maths::Vector2i(70, 70));
        sprite->SetBegin(sf::Vector2i(0, 0));
        sprite->SetEnd(sf::Vector2i(5, 1));
        sprite->SetAutoIncrement(true);


        return game_object;
    }

    void SetColor(std::string _color) {
        std::cout << "Pink" << std::endl;
        AssetModule::AddAsset("player", "../Assets/Sprites/CharacterSpriteSheet" + _color + ".png");
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<MenuScene>();
    }
};
