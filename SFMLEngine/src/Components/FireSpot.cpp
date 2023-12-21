#include "Components/FireSpot.h"
#include "Components/SpriteRenderer.h"
#include "Components/Character.h"
#include "Modules/AssetModule.h"


void FireSpot::Update(float _delta_time) {
    Component::Update(_delta_time);
    count += _delta_time;
    GameObject* player = scene->GetPlayer();
    if ((player->GetPosition() - GetOwner()->GetPosition()).Magnitude() < 15) {
        
        Burning();
    }
}

void FireSpot::Burning() {
    if (count >= 1.f) {
        AssetModule::PlaySound("fire_burning");
        count = 0.f;
        Character::SetHealth(-10);
        std::cout << "Player is burning" << std::endl;
    }

}