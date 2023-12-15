#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include "Components/PathFinding.h"

std::deque<Maths::Vector2f> PathFinding::FindPath(const Maths::Vector2f& start, const Maths::Vector2f& goal, const std::vector<SquareCollider*>& colliders) {
    struct NodeComparator {
        bool operator()(const Node* lhs, const Node* rhs) const {
            return lhs->getFScore() > rhs->getFScore();
        }
    };

    std::cout << "LOOKING FOR A PATH";

    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> openSet;
    std::vector<Node*> openSetVector;  // Utilisez un vecteur pour l'itération

    std::unordered_set<Node*, Node::Hash> closedSet;

    Node* startNode = new Node(start, 0.0f, 0.0f, nullptr);
    openSet.push(startNode);
    openSetVector.push_back(startNode);

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        // Supprimez également le nœud du vecteur
        auto eraseIt = std::remove(openSetVector.begin(), openSetVector.end(), current);
        openSetVector.erase(eraseIt, openSetVector.end());

        std::cout << "Processing node: (" << current->position.x << ", " << current->position.y << ")" << std::endl;

        if (current->position.x == goal.x && current->position.y == goal.y) {
            // Goal reached, reconstruct and return the path
            std::deque<Maths::Vector2f> path = reconstructPath(current);
            // Nettoyer les nœuds alloués
            while (!openSet.empty()) {
                delete openSet.top();
                openSet.pop();
            }
            for (Node* node : closedSet) {
                delete node;
            }
            std::cout << "PATH FOUND" << std::endl;
            return path;
        }

        closedSet.insert(current);

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) {
                    continue; // Ignorer la position actuelle
                }

                Maths::Vector2f neighborPos = { current->position.x + dx, current->position.y + dy };

                if (!isValidPosition(neighborPos, colliders)) {
                    std::cout << "Invalid position: (" << neighborPos.x << ", " << neighborPos.y << ")" << std::endl;
                    continue; // Ignorer les positions invalides
                }

                float gScore = current->gScore + std::sqrt(dx * dx + dy * dy);
                float hScore = std::sqrt((goal.x - neighborPos.x) * (goal.x - neighborPos.x) +
                    (goal.y - neighborPos.y) * (goal.y - neighborPos.y));

                Node* neighbor = new Node(neighborPos, gScore, hScore, current);

                // Ignorer si le voisin est déjà dans l'ensemble fermé
                if (closedSet.find(neighbor) != closedSet.end()) {
                    std::cout << "Neighbor in closed set: (" << neighborPos.x << ", " << neighborPos.y << ")" << std::endl;
                    delete neighbor;
                    continue;
                }

                // Ignorer si le voisin est déjà dans l'ensemble ouvert avec un score F inférieur
                auto openSetIterator = std::find_if(openSetVector.begin(), openSetVector.end(),
                    [neighbor](const Node* n) { return n->position == neighbor->position && n->getFScore() < neighbor->getFScore(); });

                if (openSetIterator != openSetVector.end()) {
                    std::cout << "Neighbor in open set with lower F score: (" << neighborPos.x << ", " << neighborPos.y << ")" << std::endl;
                    delete neighbor;
                    continue;
                }

                // Ajouter le voisin à l'ensemble ouvert
                openSet.push(neighbor);
                openSetVector.push_back(neighbor);

                std::cout << "Added neighbor: (" << neighborPos.x << ", " << neighborPos.y << ")" << std::endl;
            }
        }

        // Retirez le nœud actuel de l'ensemble ouvert et du vecteur
        delete current;
    }

    std::cout << "NO PATH FOUND" << std::endl;

    // Pas de chemin trouvé
    return {};
}

void PathFinding::Update(float _delta_time) {
    Maths::Vector2f entityPosition = GetOwner()->GetPosition(); /* initial position of your entity */
    // Assume path is the result obtained from the A* algorithm

    if (!path.empty()) {
        std::cout << "MOVING";
        // Get the next position in the path
        Maths::Vector2f nextPosition = path.front();

        // Move the entity towards the next position
        // You can use your own logic to smoothly move the entity
        entityPosition.x += (nextPosition.x - entityPosition.x) * 20;
        entityPosition.y += (nextPosition.y - entityPosition.y) * 20;

        // Check if the entity has reached the next position (you can define a threshold)
        if ((entityPosition - nextPosition).Magnitude() < 1.0f) {
            // Remove the current position from the path
            path.pop_front();
        }

        // Update the entity's position in your game/rendering system
        // For example, if you're using SFML, you might do something like:
        // entity.setPosition(entityPosition.x, entityPosition.y);

        // Your game loop or rendering logic continues...
    }
}