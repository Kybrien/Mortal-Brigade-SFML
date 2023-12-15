#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#include "Component.h"
#include "Components/SquareCollider.h"

namespace {
    struct Node {
        Maths::Vector2f position;
        float gScore;
        float hScore;
        Node* parent;

        Node(const Maths::Vector2f& _position, float _gScore, float _hScore, Node* _parent)
            : position(_position), gScore(_gScore), hScore(_hScore), parent(_parent) {}

        float getFScore() const {
            return gScore + hScore;
        }

        bool operator==(const Node& other) const {
            return position.x == other.position.x && position.y == other.position.y;
        }

        struct Hash {
            size_t operator()(const Node* node) const {
                return std::hash<float>()(node->position.x) ^ std::hash<float>()(node->position.y);
            }
        };
    };

    struct NodeComparator {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->getFScore() > rhs->getFScore();
        }
    };

    bool isValidPosition(const Maths::Vector2f& position, const std::vector<SquareCollider*>& colliders) {
        // Vérifier si la position est à l'intérieur des limites et ne rentre en collision avec aucun SquareCollider
        GameObject temp_obj;
        temp_obj.SetPosition(position);
        SquareCollider* s_pos = temp_obj.CreateComponent<SquareCollider>();
        s_pos->SetWidth(0.f);
        s_pos->SetHeight(0.f);
        for (const SquareCollider* collider : colliders) {
            if (SquareCollider::IsColliding(*s_pos, *collider)) {
                return false;  // Collision détectée
            }
        }
        return true;
    }

    std::deque<Maths::Vector2f> reconstructPath(Node* goalNode) {
        std::deque<Maths::Vector2f> path;
        Node* current = goalNode;

        while (current != nullptr) {
            path.push_front(current->position);
            current = current->parent;
        }

        return path;
    }
}

class PathFinding : public Component
{
public:
    std::deque<Maths::Vector2f> FindPath(const Maths::Vector2f& start, const Maths::Vector2f& goal, const std::vector<SquareCollider*>& colliders);

    void Update(float _delta_time) override;

private:
    const std::vector<SquareCollider*> collisions;
    Maths::Vector2f target;
    std::deque<Maths::Vector2f> path;
};