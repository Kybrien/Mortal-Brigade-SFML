#pragma once
#include "Scene.h"
#include "TextRenderer.h"
#include "CoolDownComponent.h"
#include "Character.h"
#include "DefaultScene.h"

class DefaultScene;

class QuotasReached : public Scene {
public:
    QuotasReached() :  Scene("QuotasReached") {

        GameObject* select_text = CreateSelectTextGameObject("SelectionText", Maths::Vector2f(0.5f, 0.5f));

        std::function<void()> changeScene = [this]() { QuotasOK(); };

        GameObject* coolDown = CreateCoolDownGameObject("SelectionText", 5.f, changeScene);

    }

    GameObject* CreateSelectTextGameObject(const std::string& _name, const Maths::Vector2f& _position) {
        GameObject* game_object = CreateGameObject(_name);

        Character::GetInventory()->NextQuotas();

        TextRenderer* text = game_object->CreateComponent<TextRenderer>();
        text->SetText("Quotas Reached ! New Quotas is : " + std::to_string(static_cast<int>(Character::GetInventory()->GetQuotas())) + " !");
        text->SetColor(sf::Color::White);
        text->SetPosition(_position);
        text->SetSize(48);
        text->Center(true);

        return game_object;
    }

    GameObject* CreateCoolDownGameObject(const std::string& _name, const float _timeToWait, const std::function<void()> _func) {
        GameObject* game_object = CreateGameObject(_name);

        CoolDown* cd = game_object->CreateComponent<CoolDown>();
        cd->SetTimeToWait(_timeToWait);
        cd->SetFunc(_func);

        return game_object;
    }

    void QuotasOK() {
        Character::GetMoonVisited()->clear();
        Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->SetScene<DefaultScene>();
    }

private:
    float cooldown = 0;
};