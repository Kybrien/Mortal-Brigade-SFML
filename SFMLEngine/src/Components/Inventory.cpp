#include "Components/Inventory.h"
#include <iostream>

void Inventory::Add(std::string _item, int _amount)
{
	for (size_t i = 0; i < inventory.size(); i++) {
		if (inventory[i].find(_item) != inventory[i].end()) {
			inventory[i][_item] += _amount;
			return;
		}
	}

	std::map<std::string, int> new_obj;
	new_obj[_item] = _amount;

	inventory.push_back(new_obj);

	return;
}

void Inventory::Remove(std::string _item, int _amount)
{
	for (size_t i = 0; i < inventory.size(); i++) {
		if (inventory[i].find(_item) != inventory[i].end()) {
			if (inventory[i][_item] - _amount > 0) {
				inventory[i][_item] -= _amount;
			}
			else {
				inventory.erase(inventory.begin()+i);
			}
			return;
		}
	}
}

void Inventory::DisplayInventory() {
	std::cout << "INVENTORY:" << std::endl;

	for (size_t i = 0; i < inventory.size(); i++) {
		for (auto it = inventory[i].begin(); it != inventory[i].end(); it++) {
			std::cout << "Item: " << it->first << ", Amount: " << it->second << std::endl;
		}
	}
}
