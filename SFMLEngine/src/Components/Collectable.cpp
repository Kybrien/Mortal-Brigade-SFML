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
        inventory->AddMoney(GetPrice());

        inventory->DisplayInventory();
        std::cout << "Total Money: " << inventory->GetTotalMoney() << std::endl;

        if (inventory->GetTotalMoney() >= 100.0f) {
            std::cout << "Vous avez atteint 100 sur 100 ! Vous pouvez retourner au vaisseau !" << std::endl;
        }

        delete GetOwner();
    }
}
