#pragma once
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Scene.h"


class MineElec : public Component {
public:
    void Update(float _delta_time) override;
    void Explode();

    void SetScene(Scene* _scene) { scene = _scene; };

private:
    Scene* scene = nullptr;
    bool isExploded = false;
};
