#include "Components/FireSpot.h"
#include "Components/SpriteRenderer.h"
#include "Components/Health.h"



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
        count = 0.f;
        GameObject* player = scene->FindGameObject("Player");
        player->GetComponent<Health>()->TakeDamage(10);
        std::cout << "Player is burning" << std::endl;
    }

}