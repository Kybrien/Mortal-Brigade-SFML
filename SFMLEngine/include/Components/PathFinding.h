#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#include "Maths/Vector2.h"
#include "Component.h"
#include "Components/SquareCollider.h"

struct Node {
	float x, y;
	int G, H;
	Node* parent;

	Node(float x, float y, Node* parent = nullptr) : x(x), y(y), G(0), H(0), parent(parent) {}
	Node(Maths::Vector2f pos, Node* parent = nullptr) : x(pos.x), y(pos.y), G(0), H(0), parent(parent) {}

	int F() const { return G + H; }

	bool operator == (const Node& other) const {
		return x == other.x && y == other.y;
	}
};

struct NodeHash {
	size_t operator()(const Node* node) const {
		return std::hash<float>()(node->x) ^ std::hash<float>()(node->y);
	}
};

struct NodeEqual {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return lhs->x == rhs->x && lhs->y == rhs->y;
	}
};

struct CompareNode {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return lhs->F() > rhs->F();
	}
};

class PathFinding : public Component
{
public:
    std::vector<Node> FindPath(std::vector<SquareCollider*> obstacles, Maths::Vector2f start, GameObject* _player);

	void Follow(float _delta_time, float _speed);

	void MovePointAlongPath(Maths::Vector2f point, float speed, float _delta_time);

    void Update(float _delta_time) override;

protected:
	std::vector<Node> path;

private:
	std::vector<SquareCollider*> collisions;
	GameObject* player;
	Maths::Vector2<float> playerLastPos;

	float heuristic(Node a, Node b) {
		// Euclidean distance (for diagonal movements)
		return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
	}

	bool isColliding(const std::vector<SquareCollider*>& obstacles, float x, float y) {
		//GameObject* temp_obj = new GameObject;
		//temp_obj->SetPosition(Maths::Vector2f(x, y));
		//SquareCollider* tempCollider = temp_obj->CreateComponent<SquareCollider>();
		//tempCollider->SetWidth(1.f);
		//tempCollider->SetHeight(1.f);

		//int collisions = 0;

		//for (const auto& collider : obstacles) {
		//	if (SquareCollider::IsColliding(*tempCollider, *collider)) {
		//		delete temp_obj;
		//		return true;
		//	}
		//}

		//delete temp_obj;
		//return false;

		for (const auto& collider : obstacles) {
			if (collider->GetOwner()->GetPosition().x == x && collider->GetOwner()->GetPosition().y == y) {
				return true; // Collision détectée
			}
		}

		return false; // Aucune collision détectée
	}

	float distance(const Node& node2, const Node& node1) {
		float dx = static_cast<float>(node1.x - node2.x);
		float dy = static_cast<float>(node1.y - node2.y);
		return std::sqrt(dx * dx + dy * dy);
	}

	Maths::Vector2f GetNearestGridPosition(Maths::Vector2f playerPosition, int gridSize) {
		// Divisez la position du joueur par la taille de la grille
		float gridX = playerPosition.x / gridSize;
		float gridY = playerPosition.y / gridSize;

		// Arrondissez les coordonnées à l'entier le plus proche
		int nearestGridX = std::round(gridX);
		int nearestGridY = std::round(gridY);

		// Nouvelles coordonnées de la case la plus proche
		Maths::Vector2f nearestGridPosition;
		nearestGridPosition.x = nearestGridX * gridSize;
		nearestGridPosition.y = nearestGridY * gridSize;

		return nearestGridPosition;
	}
};