#pragma once
#include <iostream>
#include <functional>

#include "Engine.h"
#include "Modules/InputModule.h"
#include "Modules/AssetModule.h"

#include "Scene.h"
#include "Button.h" 
#include "BackgroundRenderer.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "Map1.h"
#include "Map2.h"
#include "Map3.h"


class ChooseMap : public Scene {
public:
    ChooseMap() : Scene("ChooseMapScene") {
        // Création de l'arrière-plan pour la sélection de la carte
        GameObject* background = CreateBackgroundGameObject("MapSelectionBackground", "map_selection_background");

        AssetModule::Play("moon_selection");
        AssetModule::Loop(true);

        std::function<void()> goToMap1_func = [this]() { GoToMap1(); };
        std::function<void()> goToMap2_func = [this]() { GoToMap2(); };
        std::function<void()> goToMap3_func = [this]() { GoToMap3(); };

        GameObject* mapButton1 = CreateMapButton("Map1Button", 250.f, 300.f, "moon_1" , goToMap1_func);
        GameObject* mapButton2 = CreateMapButton("Map2Button", 850.f, 300.f, "moon_2" , goToMap2_func);
        GameObject* mapButton3 = CreateMapButton("Map3Button", 1450.f, 300.f, "moon_3", goToMap3_func);
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texture_path) {
        GameObject* game_object = CreateGameObject(_name);
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texture_path);
        return game_object;
    }

    GameObject* CreateMapButton(const std::string& _name, float _x, float _y, const std::string& _texture_path, std::function<void()> func) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton pour choisir une carte
        Button* button = game_object->CreateComponent<Button>();
        button->SetSize(Maths::Vector2f(300.f, 300.f));
        button->SetColor(sf::Color(0, 0, 0, 0));
        button->OnClick(func);
        button->SetBaseSize(3.f);
        button->SetHoverSize(3.5f);
        button->Animate(true);
        SpriteRenderer* sprite = game_object->CreateComponent<SpriteRenderer>();
        sprite->LoadSprite(_texture_path);
        sprite->SetTextureSize(Maths::Vector2u(100, 100));
        sprite->SetAutoIncrement(true);
        sprite->SetScale(3.f);
        sprite->SetBegin(sf::Vector2i(0, 0));
        sprite->SetEnd(sf::Vector2i(49, 0));
        

        return game_object;
    }

    void GoToMap1() {
        std::cout << "test" << std::endl;
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<Map1>();
        AssetModule::Stop();
    }
    void GoToMap2() {
        std::cout << "test" << std::endl;
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<Map2>();
        AssetModule::Stop();
    }
    void GoToMap3() {
        std::cout << "test" << std::endl;
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<Map3>();
        AssetModule::Stop();
    }

};