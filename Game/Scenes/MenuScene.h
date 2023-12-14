#pragma once
#include "Scene.h"
#include "Button.h" 
#include "BackgroundRenderer.h"
#include "RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include <iostream>

class MenuScene final : public Scene {
public:
    MenuScene() : Scene("MenuScene") {
        // Création de l'arrière-plan du menu (supposons que vous avez une classe Background)
        GameObject* background = CreateBackgroundGameObject("Background", "../Assets/Images/menu_background.png");

        // Création des boutons du menu
        GameObject* playButton = CreateButtonGameObject("PlayButton", 792.f, 300.f, "Play");
        GameObject* optionsButton = CreateButtonGameObject("OptionsButton", 930.f, 300.f, "Options");
        GameObject* creditsButton = CreateButtonGameObject("CreditsButton", 792.f, 403.f, "Credits");
        GameObject* leaveButton = CreateButtonGameObject("LeaveButton", 930.f, 403.f, "Leave");
    }
    
    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texturePath) {
        GameObject* game_object = CreateGameObject(_name);
        // Code pour charger et définir la texture pour l'arrière-plan

        // Supposons que vous ayez une classe BackgroundRenderer pour rendre l'arrière-plan
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texturePath); // Charger la texture de l'arrière-plan  

        return game_object;
    }

    GameObject* CreateButtonGameObject(const std::string& _name, float _x, float _y, const std::string& _text) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton avec du texte
        Button* button = game_object->CreateComponent<Button>();
        button->SetText(_text);
        button->SetColor(sf::Color::Red);
        button->SetSize(Maths::Vector2f(100.f, 100.f));

        return game_object;
    }

};
