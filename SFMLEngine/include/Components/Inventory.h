#pragma once
#include <iostream>
#include <map>
#include "Component.h"

class Inventory : public Component
{
public:
    void Add(std::string _item, int _amount);
    void Remove(std::string _item, int _amount);
    void Reset() { inventory.clear(), totalMoney = 0; };

    //DEBUG
    void DisplayInventory();
    //

    std::vector<std::map<std::string, int>> GetInventory() { return inventory; }

    float GetTotalMoney() const { return totalMoney; }
    void AddMoney(float amount) { totalMoney += amount; }
    float GetQuotas() { return quotas; }
    void NextQuotas() { quotas *= 2.f; }

private:
    std::vector<std::map<std::string, int>> inventory;
    float totalMoney = 0.0f;
    float quotas = 100.f;

};
