#include "Modules/AssetModule.h"
#include "Components/Red.h"
#include "Components/SpriteRenderer.h"

void RED::Update(float _delta_time) {
	SetCooldown(_delta_time);
	if (IsPlayerInRange()) {
		SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
		sprite->SetBegin(sf::Vector2i(0, 2));
		sprite->SetEnd(sf::Vector2i(9, 2));

		if (!sound_playing) {
			AssetModule::SetSoundVolume("monster_red_kill", 25.f);
			AssetModule::PlaySound("monster_red_chase");
			AssetModule::LoopSound("monster_red_chase", true);
			sound_playing = true;
		}
		if (path.empty()) {
			FindPath(scene->GetColliders(), GetOwner()->GetPosition(), scene->GetPlayer());
		}
	}
	if (!IsPlayerInRange()) {
		sound_playing = false;
		AssetModule::StopSound("monster_red_chase");
	}

	if (!path.empty()) {
		Follow(_delta_time, speed);
	}
}