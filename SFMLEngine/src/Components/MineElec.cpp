#include "Components/MineElec.h"
#include "Components/SpriteRenderer.h"
#include "Components/Character.h"



void MineElec::Update(float _delta_time) {
    Component::Update(_delta_time);
    GameObject* player = scene->GetPlayer();
    if ((player->GetPosition() - GetOwner()->GetPosition()).Magnitude() < 20) {
        Explode();
    }
}

void MineElec::Explode() {
    if (!isExploded) {
        isExploded = true;
        GameObject* player = scene->FindGameObject("Player");
        Character::SetHealth(-100);
        std::cout << "BZZZZ - Electrocution le joueur est mort" << std::endl;

        //Generation du sprite
        SpriteRenderer* sprite_renderer = GetOwner()->GetComponent<SpriteRenderer>();
        sprite_renderer->LoadSprite("thunderstrike");
        GetOwner()->SetPosition(GetOwner()->GetPosition() - Maths::Vector2f(40, 75));
        sprite_renderer->SetTextureSize(Maths::Vector2u(64, 64));
        sprite_renderer->SetScale(1.5f);
        sprite_renderer->SetAnimSpeed(1.0f);
        sprite_renderer->SetAutoIncrement(true);
        sprite_renderer->SetBegin(sf::Vector2i(0, 0));
        sprite_renderer->SetEnd(sf::Vector2i(11, 0));
        sprite_renderer->SetOffset(Maths::Vector2i(0, 0));
        sprite_renderer->SetLoop(false);
    }
}