#pragma once
#include <iostream>
#include <functional>

#include "Engine.h"
#include "Modules/InputModule.h" // Inclure le gestionnaire d'entrée

#include "Scene.h"
#include "Button.h" 
#include "BackgroundRenderer.h"
#include "PauseComponent.h"

class MenuPause final : public Scene {
public:
    MenuPause() : Scene("MenuPause") {
        // Création de l'arrière-plan du menu pause (supposons que vous avez une classe Background)
        GameObject* background = CreateBackgroundGameObject("PauseBackground", "pause_background");

        // Création des boutons du menu pause
        std::function<void()> resume_func = [this]() { Resume(); };
        std::function<void()> quit_func = [this]() { Quit(); };

        GameObject* resumeButton = CreateButtonGameObject("ResumeButton", 792.f, 300.f, "Resume", resume_func);
        GameObject* quitButton = CreateButtonGameObject("QuitButton", 792.f, 403.f, "Quit", quit_func);
    }

    void Resume() {
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->RemoveScene("MenuPause");
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetMainScene("DefaultScene");
    }

    void Quit() {
        Engine::GetInstance()->Quit();
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texturePath) {
        GameObject* game_object = CreateGameObject(_name);
        // Code pour charger et définir la texture pour l'arrière-plan
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texturePath); // Charger la texture de l'arrière-plan  

        return game_object;
    }

    GameObject* CreateButtonGameObject(const std::string& _name, float _x, float _y, const std::string& _text, std::function<void()> _func) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton avec du texte
        Button* button = game_object->CreateComponent<Button>();
        button->SetText(_text);
        button->SetSize(Maths::Vector2f(100.f, 100.f));
        button->SetColor(sf::Color(0, 0, 255, 255));
        button->OnClick(_func);

        return game_object;
    }

    GameObject* CreatePauseMenu(std::function<void()> _func) {
        GameObject* game_object = CreateGameObject("Pause");

        PauseComponent* resume = game_object->CreateComponent<PauseComponent>();
        resume->Execute(_func);

        return game_object;

    }


};