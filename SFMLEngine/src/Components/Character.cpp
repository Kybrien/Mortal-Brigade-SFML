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

void Character::SetStamina(float _stamina) {
	if ((stamina + _stamina) > maxStamina) {
		stamina = maxStamina;
	}
	else if (stamina + _stamina < 0.f) {
		stamina = 0.f;
	}
	else {
		stamina += _stamina;
	}
}


int Character::maxHealth = 0;
int Character::health = 0;
float Character::maxStamina = 0;
float Character::stamina = 0;
Inventory* Character::inventory = nullptr;
SpriteRenderer* Character::spriteRenderer = nullptr;
TextRenderer* Character::quotaUI = nullptr;
