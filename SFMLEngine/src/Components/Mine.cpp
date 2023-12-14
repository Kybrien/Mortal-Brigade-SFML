#include "Components/Mine.h"
#include "Components/SpriteRenderer.h"

void Mine::Update(float _delta_time) {
    Component::Update(_delta_time);
    if (isExploded) {
        // Gérer la logique post-explosion ici, si nécessaire
    }
}

void Mine::Explode() {
    if (!isExploded) {
        isExploded = true;
        //spriteRenderer->LoadSprite("chemin/vers/l'animation/explosion.png");
        // Autres actions d'explosion (son, particules, etc.)
    }
}