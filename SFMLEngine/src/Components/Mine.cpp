#include "Components/Mine.h"
#include "Components/SpriteRenderer.h"
#include "Components/Health.h"


void Mine::Update(float _delta_time) {
    Component::Update(_delta_time);
    GameObject* player = scene->FindGameObject("Player");
    if ((player->GetPosition() - GetOwner()->GetPosition()).Magnitude() < 20) {
        Explode();
        // Gerer la logique post-explosion ici, si necessaire
    }
}

void Mine::Explode() {
    if (!isExploded) {
        isExploded = true;
        GameObject* player = scene->FindGameObject("Player");
        player->GetComponent<Health>()->TakeDamage(100);
        std::cout << "BOOM" << std::endl;
        spriteRenderer->LoadSprite("chemin/vers/l'animation/explosion.png");
        // Autres actions d'explosion (son, particules, etc.)
    }
}