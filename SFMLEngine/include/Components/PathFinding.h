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

class PathFinding : public Component
{
public:
    std::vector<Node> FindPath(std::vector<SquareCollider*> obstacles, Maths::Vector2f start, Maths::Vector2f end);

	void MovePointAlongPath(Maths::Vector2f point, float speed, float _delta_time);

    void Update(float _delta_time) override;

private:
    const std::vector<SquareCollider*> collisions;
    //Maths::Vector2f target;
    std::vector<Node> path;

	int heuristic(Node a, Node b) {
		// Euclidean distance (for diagonal movements)
		return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
	}

	bool isColliding(const std::vector<SquareCollider*>& obstacles, float x, float y) {
		GameObject* temp_obj = new GameObject;
		temp_obj->SetPosition(Maths::Vector2f(x, y));
		SquareCollider* tempCollider = temp_obj->CreateComponent<SquareCollider>();
		tempCollider->SetOwner(temp_obj); // Creating a temporary GameObject for the collider
		tempCollider->SetWidth(1.f);
		tempCollider->SetHeight(1.f);

		for (const auto& collider : obstacles) {
			if (SquareCollider::IsColliding(*tempCollider, *collider)) {
				delete temp_obj; // Important to clean up the temporary GameObject
				return true;
			}
		}

		delete temp_obj; // Clean up the temporary GameObject
		return false;
	}
};