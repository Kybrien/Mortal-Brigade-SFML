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
			std::cout << "sound red" << std::endl;
			AssetModule::PlaySound("red_chase");
			AssetModule::SetSoundVolume("red_chase", 25.f);
			AssetModule::LoopSound("red_chase", true);
			sound_playing = true;
		}
		if (path.empty()) {
			FindPath(scene->GetColliders(), GetOwner()->GetPosition(), scene->GetPlayer());
		}
	}
	if (!IsPlayerInRange() && sound_playing == true) {
		sound_playing = false;
		AssetModule::StopSound("red_chase");
	}

	if (!path.empty()) {
		Follow(_delta_time, speed);
	}
}