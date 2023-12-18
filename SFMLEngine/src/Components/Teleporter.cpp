#include <iostream>
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Components/Teleporter.h"
#include "Components/SquareCollider.h"

void Teleporter::Update(float _delta_time) {
	GameObject* player = current_scene->GetPlayer();

	std::cout << "jexiste";

	if (player && SquareCollider::IsColliding(*player->GetComponent<SquareCollider>(), *GetOwner()->GetComponent<SquareCollider>()) && !teleported) {
		teleported = true;

		func();
	}
}