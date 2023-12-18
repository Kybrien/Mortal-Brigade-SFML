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

class MenuScene final : public Scene {
public:
    MenuScene() : Scene("MenuScene") {
        // Création de l'arrière-plan du menu (supposons que vous avez une classe Background)
        GameObject* background = CreateBackgroundGameObject("Background", "menu_background");

        AssetModule::Play("menu");
        AssetModule::Loop(true);

        // Création des boutons du menu
        std::function<void()> play_func = [this]() { Play(); };
        std::function<void()> quit_func = [this]() { Quit(); };
        std::function<void()> empty_func = [this]() { EmptyFunc(); };

        GameObject* playButton = CreateButtonGameObject("PlayButton", 792.f, 300.f, "Play", play_func);
        //GameObject* optionsButton = CreateButtonGameObject("OptionsButton", 930.f, 300.f, "Options", play_func);
        //GameObject* creditsButton = CreateButtonGameObject("CreditsButton", 930.f, 403.f, "Credits", play_func);
        GameObject* leaveButton = CreateButtonGameObject("LeaveButton", 792.f, 403.f, "Leave", quit_func);
    }

    void Play() {
        std::cout << "test" << std::endl;
        AssetModule::Stop();
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<DefaultScene>();
    }

    void Quit() {
        Engine::GetInstance()->Quit();
    }

    void EmptyFunc() {

    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texture) {
        GameObject* game_object = CreateGameObject(_name);
        // Code pour charger et définir la texture pour l'arrière-plan

        // Supposons que vous ayez une classe BackgroundRenderer pour rendre l'arrière-plan
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texture); // Charger la texture de l'arrière-plan  

        return game_object;
    }

    GameObject* CreateButtonGameObject(const std::string& _name, float _x, float _y, const std::string& _text, std::function<void()> func) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton avec du texte
        Button* button = game_object->CreateComponent<Button>();
        button->SetText(_text);
        button->SetSize(Maths::Vector2f(100.f, 100.f));
        button->SetColor(sf::Color(0, 0, 0, 0));
        button->OnClick(func);

        return game_object;
    }

};