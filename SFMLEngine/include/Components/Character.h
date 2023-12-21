#pragma once
#include "Component.h"
#include "Inventory.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class Character : public Component {
public:
	Character();

	static void SetMaxHealth(int _maxHealth) { maxHealth = _maxHealth, health = _maxHealth; }
	static void SetHealth(int _health);
	static void SetInventory(Inventory* _inventory) { inventory = _inventory; }
	static void SetSpriteRenderer(SpriteRenderer* _spriteRenderer) { spriteRenderer = _spriteRenderer; }
	static void SetQuotaUI(TextRenderer* _quotaUI) { quotaUI = _quotaUI; }

	static int GetHealth() { return health; }
	static int GetMaxHealth() { return maxHealth; }
	static Inventory* GetInventory() { return inventory; }
	static SpriteRenderer* GetSpriteRenderer() { return spriteRenderer; }
	static TextRenderer* GetQuotaUI() { return quotaUI; }

private:
	static int maxHealth;
	static int health;
	static Inventory* inventory;
	static SpriteRenderer* spriteRenderer;
	static TextRenderer* quotaUI;
};
