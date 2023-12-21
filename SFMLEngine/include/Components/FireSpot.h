#pragma once
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Scene.h"


class FireSpot : public Component {
public:
    void Update(float _delta_time) override;
    void Burning();

    void SetScene(Scene* _scene) { scene = _scene; };


private:
    Scene* scene = nullptr;
    bool isBurning = false;
    float count = 1.f;
};
