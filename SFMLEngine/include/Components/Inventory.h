#pragma once
#include <iostream>
#include <map>
#include "Component.h"

class Inventory : public Component
{
public:
    void Add(std::string _item, int _amount);
    void Remove(std::string _item, int _amount);
    void ResetInventory() { inventory.clear(), totalMoney = 0.f; };
    void ResetQuotas() { quotas = 10.f; };

    //DEBUG
    void DisplayInventory();
    //

    std::vector<std::map<std::string, int>> GetInventory() { return inventory; }

    float GetTotalMoney() const { return totalMoney; }
    void AddMoney(float amount) { totalMoney += amount; }
    float GetQuotas() { return quotas; }
    void NextQuotas() { inventory.clear(), totalMoney = 0, quotas *= 2.f; }

private:
    std::vector<std::map<std::string, int>> inventory;
    float totalMoney = 0.0f;
    float quotas = 10.f;

};
