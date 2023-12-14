#pragma once
#include "Component.h"

class Health : public Component {
public:
	void SetMaxHealth(const int _max_health);
	void SetHealth(const int _health);

	int GetMaxHealth() const { return max_health; }
	int GetHealth() const { return health; }

	void TakeDamage(const int _damage);

private:
	int max_health = 100;
	int health = 100;
};