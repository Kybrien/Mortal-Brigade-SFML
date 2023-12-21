#pragma once
#include <iostream>
#include "Components/Collectable.h"
#include "Components/Inventory.h"
#include "Modules/SceneModule.h"
#include "Components/Character.h"
#include "Components/TextRenderer.h"
#include "Modules/AssetModule.h"

void Collectable::Prompt() {
    std::cout << "Collecting !!";
    Inventory* inventory = Character::GetInventory();

    if (inventory) {
        inventory->Add(name, 1);
        inventory->AddMoney(GetPrice());
        TextRenderer* quotas = Character::GetQuotaUI();
        quotas->SetText("Quota:" + std::to_string(static_cast<int>(Character::GetInventory()->GetTotalMoney())) + "/" + std::to_string(static_cast<int>(Character::GetInventory()->GetQuotas())));
        if (Character::GetInventory()->GetTotalMoney() >= Character::GetInventory()->GetQuotas()) {
            quotas->SetColor(sf::Color::Green);
        }
        else {
            quotas->SetColor(sf::Color::White);
        }

        inventory->DisplayInventory();
        std::cout << "Total Money: " << inventory->GetTotalMoney() << std::endl;

        if (inventory->GetTotalMoney() >= 100.0f) {
            std::cout << "Vous avez atteint 100 sur 100 ! Vous pouvez retourner au vaisseau !" << std::endl;
        }

        GetOwner()->SetActive(false);
        //delete GetOwner();
    }
}
