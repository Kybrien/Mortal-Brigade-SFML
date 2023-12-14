#pragma once
#include "Scene.h"
#include "Button.h" 
#include "BackgroundRenderer.h"
#include "RectangleShapeRenderer.h"
#include "Modules/InputModule.h"
#include <iostream>

class ChooseMap : public Scene {
public:
    ChooseMap() : Scene("ChooseMapScene") {
        // Création de l'arrière-plan pour la sélection de la carte
        GameObject* background = CreateBackgroundGameObject("MapSelectionBackground", "../Assets/Images/map_selection_bg.png");

        GameObject* mapButton1 = CreateMapButton("Map1Button", 300.f, 250.f, "Map 1");
        GameObject* mapButton2 = CreateMapButton("Map2Button", 900.f, 250.f, "Map 2");
        GameObject* mapButton3 = CreateMapButton("Map3Button", 1500.f, 250.f, "Map 3");
    }

    GameObject* CreateBackgroundGameObject(const std::string& _name, const std::string& _texturePath) {
        GameObject* game_object = CreateGameObject(_name);
        BackgroundRenderer* background_renderer = game_object->CreateComponent<BackgroundRenderer>();
        background_renderer->LoadTexture(_texturePath);
        return game_object;
    }

    GameObject* CreateMapButton(const std::string& _name, float _x, float _y, const std::string& _texturePath) {
        GameObject* game_object = CreateGameObject(_name);
        game_object->SetPosition(Maths::Vector2f(_x, _y));

        // Création d'un bouton pour choisir une carte
        Button* button = game_object->CreateComponent<Button>();


        }

        return game_object;
    }

};
