#include "Components/Character.h"

Character::Character(){}

void Character::SetHealth(int _health) {
	if ((health + _health) > maxHealth) {
		health = maxHealth;
	}
	else {
		health += _health;
	}
}

int Character::maxHealth = 0;
int Character::health = 0;
Inventory* Character::inventory = nullptr;
SpriteRenderer* Character::spriteRenderer = nullptr;
