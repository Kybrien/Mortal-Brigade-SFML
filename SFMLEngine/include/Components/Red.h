#pragma once
#include "Component.h"
#include "Components/Enemy.h"
#include "Components/PathFinding.h"

class RED : public Enemy {
public:
	void Update(float _delta_time) override;

};