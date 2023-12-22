#include "Modules/AssetModule.h"
#include "Components/Lullaby.h"
#include "Components/SpriteRenderer.h"

void Lullaby::Update(float _delta_time) {
	if (IsPlayerInRange()) {
		if (sleeping) {
			SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
			sprite->SetBegin(sf::Vector2i(0, 0));
			sprite->SetEnd(sf::Vector2i(12, 0));
			sleeping = false;
			AssetModule::Stop();
			AssetModule::StopSound();
			AssetModule::Play("monster_lullaby_sleep");
		}
	}
	if (!sleeping && !chasing) {
		if (count >= sleep_time) {
			FindPath(scene->GetColliders(), GetOwner()->GetPosition(), scene->GetPlayer());
			SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
			sprite->SetBegin(sf::Vector2i(0, 1));
			sprite->SetEnd(sf::Vector2i(12, 1));
			chasing = true;
			AssetModule::Stop();
			AssetModule::StopSound();
			AssetModule::Play("monster_lullaby_scream");
		}
		else {
			count += _delta_time;
			if ((scene->GetPlayer()->GetPosition() - GetOwner()->GetPosition()).Magnitude() > 350.f) {
				SpriteRenderer* sprite = GetOwner()->GetComponent<SpriteRenderer>();
				sleeping = true;
				count = 0.f;
				AssetModule::Stop();
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