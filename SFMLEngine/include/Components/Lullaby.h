#pragma once
#include "Component.h"
#include "Components/Enemy.h"
#include "Components/PathFinding.h"

class Lullaby : public Enemy {
public:
	void Update(float _delta_time) override;
private:
	float count = 0.f;
	float sleep_time = 12.f;
	bool sleeping = true;
	bool chasing = false;
	float speed = 200.f;
};