#include "Modules/AssetModule.h"
#include "Components/Lullaby.h"
#include "Components/SpriteRenderer.h"

void Lullaby::Update(float _delta_time) {
	if (IsPlayerInRange()) {
		if (sleeping) {
			SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
			sprite->SetBegin(sf::Vector2i(0, 0));
			sprite->SetEnd(sf::Vector2i(12, 0));
			sprite->SetLoop(true);
			sleeping = false;
			AssetModule::StopSound("monster_lullaby_sleep");
			AssetModule::PlaySound("monster_lullaby_sleep");
			AssetModule::SetSoundVolume("monster_lullaby_sleep", 25.f);
		}
	}
	if (!sleeping && !chasing) {
		if (count >= sleep_time) {
			FindPath(scene->GetColliders(), GetOwner()->GetPosition(), scene->GetPlayer());
			SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
			sprite->SetBegin(sf::Vector2i(0, 1));
			sprite->SetEnd(sf::Vector2i(12, 1));
			chasing = true;
			sprite->SetLoop(false);
			AssetModule::StopSound("monster_lullaby_sleep");
			AssetModule::PlaySound("monster_lullaby_scream");
			AssetModule::SetSoundVolume("monster_lullaby_scream", 25.f);
		}
		else {
			count += _delta_time;
			if ((scene->GetPlayer()->GetPosition() - GetOwner()->GetPosition()).Magnitude() > 250.f) {
				SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
				sleeping = true;
				sprite->SetLoop(true);
				count = 0.f;
				AssetModule::StopSound("monster_lullaby_scream");
				AssetModule::StopSound("monster_lullaby_sleep");
				sprite->ResetAnimation();
				sprite->SetBegin(sf::Vector2i(0, 0));
				sprite->SetEnd(sf::Vector2i(1, 0));
			}
		}
	}
	if (chasing && !path.empty()) {
		Follow(_delta_time, speed);
	}
}