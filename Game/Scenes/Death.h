#pragma once
#include <iostream>
#include <functional>

#include "Engine.h"
#include "Character.h"
#include "Scene.h"
#include "MenuScene.h"

#include "CoolDownComponent.h"

class GameOver : public Scene {
public:
    GameOver() : Scene("GameOver") {
        // Création de l'arrière-plan de l'écran de Game Over
        GameObject* background = CreateBackgroundGameObject("GameOverBackground", "GameOverBackground");

        // Création des boutons de l'écran de Game Over
        std::function<void()> restart_func = [this]() { Restart(); };
        GameObject* coolDown = CreateCoolDownGameObject("SelectionText", 5.f, restart_func);

        Character::Reset();

        AssetModule::StopAll();
    }

    void Restart() {
        Character::Reset();
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<MenuScene>();
    }

    GameObject* CreateCoolDownGameObject(const std::string& _name, const float _timeToWait, const std::function<void()> _func) {
        GameObject* game_object = CreateGameObject(_name);
        CoolDown* cd = game_object->CreateComponent<CoolDown>();
        cd->SetTimeToWait(_timeToWait);
        cd->SetFunc(_func);

        return game_object;
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texturePath) {
        GameObject* game_object = CreateGameObject(_name);
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texturePath); // Charger la texture de l'arrière-plan  

        return game_object;
    }
};