#pragma once
#include "Components/ProximityPrompt.h"

class Collectable : public ProximityPrompt
{
public:
    void Prompt() override;
    void SetName(std::string _name) { name = _name; }
    float GetPrice() const { return price; }
    std::string GetName() { return name; }
    void SetPrice(float _price) { price = _price; }

private:
    std::string name;
    float price = 0.0f;
};