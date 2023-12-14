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
        // ... Vérification des collisions ...
    }

    std::deque<Maths::Vector2f> reconstructPath(Node* goalNode) {
        // ... Reconstruction du chemin ...
    }
}

class PathFinding : public Component
{
public:
    

private:
    const std::vector<SquareCollider*> collisions;
    Maths::Vector2f target;
    std::deque<Maths::Vector2f> path;
};