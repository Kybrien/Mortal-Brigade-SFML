#include "Components/Health.h"

void Health::SetMaxHealth(const int _max_health) {
	max_health = _max_health; health > _max_health ? health = _max_health : health = health;
}

void Health::SetHealth(const int _health) {
	health > max_health ? health = max_health : health = _health;
}

void Health::TakeDamage(const int _damage) {
	health - _damage < 0 ? health = 0 : health -= _damage;
}