#pragma once
#include "Scene.h"
#include <functional>
#include "BackgroundRenderer.h"
#include "Button.h" 
#include "SpriteRenderer.h"
#include "Engine.h"
#include "MenuScene.h"

class ChooseCharacter : public Scene {
public:
    ChooseCharacter() : Scene("ChooseCharacterScene") {
        GameObject* background = CreateBackgroundGameObject("MapSelectionBackground", "../Assets/Images/map_selection_bg.png");

        std::function<void()> selectPink = [this]() { Pink(); };
        std::function<void()> selectBlue = [this]() { Blue(); };

        GameObject* CharacterButtonPink = CreateCharacterButton("CharacterButtonPink", 500, 200.f, "CharacterSpriteSheetPink.png", selectPink);
        GameObject* CharacterButtonBlue = CreateCharacterButton("CharacterButtonBlue", 1000.f, 200.f, "CharacterSpriteSheetBlue.png", selectBlue);
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texture_path) {
        GameObject* game_object = CreateGameObject(_name);
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texture_path);
        return game_object;
    }

    GameObject* CreateCharacterButton(const std::string& _name, float _x, float _y, const std::string& _texture_path, std::function<void()> func) {
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
        sprite->LoadSprite(_texture_path);
        sprite->SetTextureSize(Maths::Vector2u(360, 300));
        sprite->SetScale(2.f);
        sprite->SetAnimSpeed(1.f);
        sprite->SetOffset(Maths::Vector2i(70, 70));
        sprite->SetBegin(sf::Vector2i(0, 0));
        sprite->SetEnd(sf::Vector2i(5, 1));
        sprite->SetAutoIncrement(true);


        return game_object;
    }

    void Pink() {
        std::cout << "Pink" << std::endl;
        chosenColor = "Pink";
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<MenuScene>();
    }

    void Blue() {
        std::cout << "Blue" << std::endl;
        chosenColor = "Blue";
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<MenuScene>();
    }

    static std::string GetChosenColor() {
        return chosenColor;
    }

private:
    static std::string chosenColor;
};

std::string ChooseCharacter::chosenColor;
