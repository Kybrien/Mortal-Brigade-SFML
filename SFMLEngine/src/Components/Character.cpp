#include "Components/Character.h"

Character::Character(){}

void Character::SetHealth(int _health) {
	if ((health + _health) > maxHealth) {
		health = maxHealth;
	}
	else {
		health += _health;
	}
	if (health <= 0) {
		std::cout << "dead" << std::endl;
		(*func)();
	}
}

int Character::maxHealth = 0;
int Character::health = 0;
Inventory* Character::inventory = nullptr;
SpriteRenderer* Character::spriteRenderer = nullptr;
TextRenderer* Character::quotaUI = nullptr;
std::vector<int>* Character::moonVisited = new std::vector<int>;
std::function<void()>* Character::func = nullptr;