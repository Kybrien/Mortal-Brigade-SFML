#pragma once
#include <string>
#include "Component.h"

class Enemy : public Component {
public:
	Enemy();

	void SetName(std::string _name) { name = _name; }
	void SetHealth(int _health) { health += _health ; }
	void SetMaxHealth(int _health) { health = _health; }
	void SetAttackSpeed(float _attackSpeed) { attackSpeed = _attackSpeed; }
	void SetCooldown(float _cooldown) { cooldown += _cooldown ; }
	void SetDamage(float _damage) { damage = _damage; }
	void SetSpeed(float _speed) { speed = _speed; }
	void SetDetectionRange(float _range) { detectionRange = _range; }
	
	std::string GetName() { return name; }
	int GetHealth() { return health; }
	float GetCooldown() { return cooldown; }
	float GetAttackSpeed() { return attackSpeed; }
	float GetDamage() { return damage; }
	float GetSpeed() { return speed; }
	float GetDetectionRange() { return detectionRange; }

	void Attack(GameObject* player);


private:
	std::string name;
	int health;
	float cooldown = 0.f;
	float attackSpeed;
	float damage;
	float speed;
	float detectionRange;
};
