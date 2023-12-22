#include "Modules/AssetModule.h"
#include "Components/Red.h"

void RED::Update(float _delta_time) {
	SetCooldown(_delta_time);
	if (IsPlayerInRange()) {
		if (path.empty()) {
			FindPath(scene->GetColliders(), GetOwner()->GetPosition(), scene->GetPlayer());
		}
	}

	if (!path.empty()) {
		Follow(_delta_time, speed);
	}
}