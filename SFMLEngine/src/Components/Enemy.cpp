#include "Components/Enemy.h"
#include"Components/Character.h"

Enemy::Enemy(){}

void Enemy::Attack(GameObject* player) {
	std::cout << "Player Life Before = " << Character::GetHealth() << std::endl;
	/*player->GetComponent<Character>()->SetHealth(-GetOwner()->GetComponent<Enemy>()->GetDamage());*/
	Character::SetHealth(-GetOwner()->GetComponent<Enemy>()->GetDamage());
	std::cout << " Attack " << std::endl;
	std::cout << "Player Life After = " << Character::GetHealth() << std::endl;
}