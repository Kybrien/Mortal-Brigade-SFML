#pragma once
#include <string>
#include "Scene.h"
#include "PathFinding.h"

class Enemy : public PathFinding {
public:
	Enemy();

	void SetHealth(int _health) { health += _health ; }
	void SetMaxHealth(int _health) { health = _health; }
	void SetAttackSpeed(float _attackSpeed) { attackSpeed = _attackSpeed; }
	void SetCooldown(float _cooldown) { cooldown += _cooldown ; }
	void SetDamage(float _damage) { damage = _damage; }
	void SetSpeed(float _speed) { speed = _speed; }
	void SetDetectionRange(float _range) { detectionRange = _range; }
	void SetScene(Scene* _scene) { scene = _scene; }
	
	int GetHealth() { return health; }
	float GetCooldown() { return cooldown; }
	float GetAttackSpeed() { return attackSpeed; }
	float GetDamage() { return damage; }
	float GetSpeed() { return speed; }
	float GetDetectionRange() { return detectionRange; }

	bool IsPlayerInRange();

	void Attack(GameObject* player);

protected:
	int health;
	float cooldown = 0.f;
	float attackSpeed;
	float damage;
	float speed;
	float detectionRange;
	Scene* scene = nullptr;
};
