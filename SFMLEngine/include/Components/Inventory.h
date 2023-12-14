#pragma once
#include <iostream>
#include <map>
#include "Component.h"

class Inventory : public Component
{
public:
	void Add(std::string _item, int _amount);
	void Remove(std::string _item, int _amount);

	//DEBUG
	void DisplayInventory();
	//

	std::vector<std::map<std::string, int>> GetInventory() { return inventory; }

private:
	std::vector<std::map<std::string, int>> inventory;
};
