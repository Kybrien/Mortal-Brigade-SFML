#include "Components/Enemy.h"
#include "Components/Character.h"

Enemy::Enemy() {
	health = 0;
	attackSpeed = 0.f;
	damage = 0.f;
	detectionRange = 0.f;
	speed = 0.f;
}

void Enemy::Attack() {
	if (cooldown >= attackSpeed) {
		Character::SetHealth(-GetOwner()->GetComponent<Enemy>()->GetDamage());
		cooldown = 0;
	}
}

bool Enemy::IsPlayerInRange() {
	if (!scene->GetPlayer())
		return false;
	if ((scene->GetPlayer()->GetPosition() - GetOwner()->GetPosition()).Magnitude() < detectionRange) {
		if ((scene->GetPlayer()->GetPosition() - GetOwner()->GetPosition()).Magnitude() < 20.f && canAttack == true) {
			Attack();
		}
		return true;
	}
	return false;
}