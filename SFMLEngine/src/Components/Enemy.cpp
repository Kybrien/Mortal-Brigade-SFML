#include "Components/Enemy.h"
#include "Components/Character.h"

Enemy::Enemy() {
	health = 0;
	attackSpeed = 0.f;
	damage = 0.f;
	detectionRange = 0.f;
	speed = 0.f;
}

void Enemy::Attack(GameObject* player) {
	/*player->GetComponent<Character>()->SetHealth(-GetOwner()->GetComponent<Enemy>()->GetDamage());*/
	Character::SetHealth(-GetOwner()->GetComponent<Enemy>()->GetDamage());
}

bool Enemy::IsPlayerInRange() {
	if (!scene->GetPlayer())
		return false;
	if ((scene->GetPlayer()->GetPosition() - GetOwner()->GetPosition()).Magnitude() < detectionRange) {
		return true;
	}
	return false;
}