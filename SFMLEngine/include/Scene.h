#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"
#include "Components/SquareCollider.h"

class Scene
{
public:
	explicit Scene(const std::string& _name);
	virtual ~Scene() = default;

	void Update(float _delta_time) const;

	void Render(sf::RenderWindow* _window) const;

	std::string GetName() const;

	GameObject* CreateGameObject(const std::string& _name);
	void DestroyGameObject(const GameObject* _game_object);
	GameObject* FindGameObject(const std::string& _name) const;

	void AddCollider(SquareCollider* collider) {
		colliders.push_back(collider);
	}

private:
	std::string name;
	std::vector<GameObject*> gameObjects;
	std::vector<SquareCollider*> colliders;
};
