#pragma once
#include "Components/ProximityPrompt.h"

class Collectable : public ProximityPrompt
{
public:
    void Prompt() override;

    float GetPrice() const { return price; }
    void SetPrice(float _price) { price = _price; }

private:
    float price = 0.0f;
};