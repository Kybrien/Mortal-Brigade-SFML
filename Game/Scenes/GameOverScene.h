#pragma once
#include "Scene.h"
#include "Button.h" 
#include "BackgroundRenderer.h"
#include "RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include "SpriteRenderer.h"

class GameOver : public Scene {
public:
    GameOver() : Scene("GameOverScene") {
        // Création de l'arrière-plan pour la sélection de la carte
        GameObject* background = CreateBackgroundGameObject("MapSelectionBackground", "../Assets/Images/GameOver_bg.jpg");

        GameObject* RetryButton = CreateOverButton("RetryButton", 250.f, 300.f, "Retry.png");
        GameObject* LeaveButton = CreateOverButton("LeaveButton", 850.f, 300.f, "Exit.png");
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texture_path) {
        GameObject* game_object = CreateGameObject(_name);
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texture_path);
        return game_object;
    }

    GameObject* CreateOverButton(const std::string& _name, float _x, float _y, const std::string& _texture_path) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton pour choisir une carte + Sprite
        Button* button = game_object->CreateComponent<Button>();
        SpriteRenderer* sprite = game_object->CreateComponent<SpriteRenderer>();
        sprite->LoadSprite(_texture_path);
        sprite->SetTextureSize(Maths::Vector2u(100, 100));
        sprite->SetAutoIncrement(true);
        sprite->SetScale(3.f);
        sprite->SetBegin(sf::Vector2i(0, 0));
        sprite->SetEnd(sf::Vector2i(49, 0));

        return game_object;
    }


};