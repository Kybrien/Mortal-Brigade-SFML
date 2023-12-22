#include "Modules/AssetModule.h"
#include "Components/Red.h"
#include "Components/SpriteRenderer.h"
#include "Modules/AssetModule.h"

void RED::Update(float _delta_time) {
	if (IsPlayerInRange()) {
		SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
		sprite->SetBegin(sf::Vector2i(0, 2));
		sprite->SetEnd(sf::Vector2i(9, 2));
		//AssetModule::PlaySound("red_chase");
		if (path.empty()) {
			FindPath(scene->GetColliders(), GetOwner()->GetPosition(), scene->GetPlayer());
		}
	}

	if (!path.empty()) {
		Follow(_delta_time, speed);
	}
}