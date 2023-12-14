#pragma once
#include <iostream>
#include "Components/Collectable.h"
#include "Components/Inventory.h"
#include "Modules/SceneModule.h"

void Collectable::Prompt() {
	std::cout << "Collecting !!";
	Inventory* inventory = current_scene->FindGameObject("Player")->GetComponent<Inventory>();

	if (inventory) {
		inventory->Add(GetOwner()->GetName(), 1);

		inventory->DisplayInventory();
	}
}