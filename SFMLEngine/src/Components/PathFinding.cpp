#include <cmath>
#include <set>
#include <algorithm>
#include <unordered_set>
#include "Components/PathFinding.h"
#include "Components/Enemy.h"

//std::vector<Node> PathFinding::FindPath(std::vector<SquareCollider*> obstacles, Maths::Vector2f start, GameObject* _player) {
//    Node* startNode = new Node(GetNearestGridPosition(start, 32));
//    Node* endNode = new Node(GetNearestGridPosition(_player->GetPosition(), 32));
//
//    std::cout << "Player pos: " << endNode->x << ", " << endNode->y << std::endl;
//    
//    std::list<Node*> openList;
//    std::list<Node*> closedList;
//    player = _player;
//    playerLastPos = player->GetPosition();
//    collisions = obstacles;
//
//    openList.push_back(startNode);
//
//    int maxIterations = 10000;
//
//    while (!openList.empty() && maxIterations > 0) {
//        auto it = std::min_element(openList.begin(), openList.end(), [](const Node* a, const Node* b) {
//            return a->F() < b->F();
//        });
//        Node* current = *it;
//
//        std::cout << "Current Node: (" << current->x << ", " << current->y << ")" << std::endl;
//
//        float distanceToEnd = distance(*current, *endNode);
//
//        if (*current == *endNode) {
//            std::cout << "Reached the end node." << std::endl;
//            std::vector<Node> new_path;
//
//            while (current->parent != nullptr) {
//                new_path.push_back(Node(current->x, current->y));
//                current = current->parent;
//                //std::cout << "Next Node: (" << current->x << ", " << current->y << "), Address: " << current << std::endl;
//                //std::cout << "Parent Node: (" << current->parent->x << ", " << current->parent->y << "), Address: " << current->parent << std::endl;
//            }
//            std::reverse(new_path.begin(), new_path.end());
//
//            // Libérer la mémoire allouée pour les nœuds
//            for (Node* node : openList) {
//                if (node != startNode && node != endNode) {
//                    delete node;
//                }
//            }
//            for (Node* node : closedList) {
//                if (node != startNode && node != endNode) {
//                    delete node;
//                }
//            }
//            delete startNode;
//            delete endNode;
//
//            path = new_path;
//
//            return new_path;
//        }
//
//        openList.erase(it);
//        closedList.push_back(current);
//
//        for (int dx = -32; dx <= 32; dx += 32) {
//            for (int dy = -32; dy <= 32; dy += 32) {
//                if (dx == 0 && dy == 0) continue;
//
//                Node* neighbor = new Node(current->x + dx, current->y + dy, current);
//
//                if (isColliding(obstacles, neighbor->x, neighbor->y)) {
//                    delete neighbor;
//                    continue;
//                }
//
//                auto openIt = std::find(openList.begin(), openList.end(), neighbor);
//                auto closedIt = std::find(closedList.begin(), closedList.end(), neighbor);
//
//                if (openIt != openList.end() && (*openIt)->G <= neighbor->G) {
//                    delete neighbor;
//                    continue;
//                }
//
//                if (closedIt != closedList.end() && (*closedIt)->G <= neighbor->G) {
//                    delete neighbor;
//                    continue;
//                }
//
//                neighbor->G = current->G + (dx == 0 || dy == 0 ? 32 : 45);
//                neighbor->H = heuristic(*neighbor, *endNode);
//
//                openList.push_back(neighbor);
//            }
//        }
//
//        maxIterations--;
//
//        if (maxIterations == 0) {
//            std::cout << "Max iterations reached. Possible infinite loop detected." << std::endl;
//        }
//    }
//
//    std::cout << "Path not found or max iterations reached." << std::endl;
//
//    // Libérer la mémoire allouée pour les nœuds
//    for (Node* node : openList) {
//        if (node != startNode && node != endNode) {
//            delete node;
//        }
//    }
//    for (Node* node : closedList) {
//        if (node != startNode && node != endNode) {
//            delete node;
//        }
//    }
//    delete startNode;
//    delete endNode;
//
//    return {}; // Return an empty path if no path is found or if max iterations reached
//}

std::vector<Node> PathFinding::FindPath(std::vector<SquareCollider*> obstacles, Maths::Vector2f start, GameObject* _player) {
    Node startNode(GetNearestGridPosition(start, 32));
    Node endNode(GetNearestGridPosition(_player->GetPosition(), 32));

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    std::unordered_set<Node*, NodeHash, NodeEqual> closedList;

    auto startNodePtr = new Node(startNode);
    openList.push(startNodePtr);
    closedList.insert(startNodePtr);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (*current == endNode) {
            std::vector<Node> new_path;
            while (current != nullptr) {
                new_path.push_back(*current);
                current = current->parent;
            }
            std::reverse(new_path.begin(), new_path.end());

            // Clean-up
            for (auto& node : closedList) {
                delete node;
            }

            path = new_path;

            return new_path;
        }

        closedList.insert(current);

        for (int dx = -32; dx <= 32; dx += 32) {
            for (int dy = -32; dy <= 32; dy += 32) {
                if (dx == 0 && dy == 0) continue;

                Node neighbor(current->x + dx, current->y + dy, current);

                if (isColliding(obstacles, neighbor.x, neighbor.y)) continue;

                if (closedList.find(&neighbor) != closedList.end()) continue;

                neighbor.G = current->G + ((dx == 0 || dy == 0) ? 32 : 45);
                neighbor.H = heuristic(neighbor, endNode);

                auto neighborPtr = new Node(neighbor);
                openList.push(neighborPtr);
                closedList.insert(neighborPtr);
            }
        }
    }

    // Clean-up
    for (auto& node : closedList) {
        delete node;
    }

    return {};  // Return an empty path if no path is found
}

void PathFinding::MovePointAlongPath(Maths::Vector2f point, float speed, float _delta_time) {
    Maths::Vector2f currentPosition = GetOwner()->GetPosition();
    Maths::Vector2f direction = (point - currentPosition).Normalize();
    Maths::Vector2f newPosition = currentPosition + direction * speed * _delta_time;

    float distance = direction.Magnitude();

    if (distance > 0.0f) {
        direction = direction.Normalize();
        Maths::Vector2f newPosition = currentPosition + direction * speed * _delta_time;
    }

    GetOwner()->SetPosition(newPosition);
}

void PathFinding::Follow(float _delta_time, float _speed) {
    if (!path.empty()) {
        Maths::Vector2f entityPosition = GetOwner()->GetPosition(); // Position initiale de l'entité
        const Node& nextNode = path.front(); // Premier Node du chemin
 
        // Position de la prochaine étape sur le chemin
        Maths::Vector2f nextPosition(nextNode.x, nextNode.y);
        // Interpolation linéaire pour un mouvement fluide

        // Vérifier si l'entité a atteint la position suivante
        float threshold = 5.0f; // Seuil de distance pour considérer la position comme atteinte
        if ((entityPosition - nextPosition).Magnitude() < threshold) {
            path.erase(path.begin()); // Retirer le Node actuel du chemin
            return;
        }

        MovePointAlongPath(nextPosition, _speed, _delta_time);
    }
}

void PathFinding::Update(float _delta_time) {
	//if (!path.empty()) {
	//	Maths::Vector2f entityPosition = GetOwner()->GetPosition(); // Position initiale de l'entité
	//	const Node& nextNode = path.front(); // Premier Node du chemin

	//	// Position de la prochaine étape sur le chemin
	//	Maths::Vector2f nextPosition(nextNode.x, nextNode.y);
	//	// Interpolation linéaire pour un mouvement fluide
	//	float speed = GetOwner()->GetComponent<Enemy>()->GetSpeed();
 //       MovePointAlongPath(nextPosition, speed, _delta_time);

	//	// Vérifier si l'entité a atteint la position suivante
	//	float threshold = 5.0f; // Seuil de distance pour considérer la position comme atteinte
	//	if ((entityPosition - nextPosition).Magnitude() < threshold) {
	//		path.erase(path.begin()); // Retirer le Node actuel du chemin
	//	}
	//}
 //   else {
 //       if (player->GetPosition() != playerLastPos && GetOwner()->GetPosition().Distance(player->GetPosition()) < GetOwner()->GetComponent<Enemy>()->GetDetectionRange()) {
 //           path.push_back(Node(player->GetPosition()));

 //           //PathFinding::FindPath(collisions, GetOwner()->GetPosition(), player);
 //       }
 //   }
 //   if (GetOwner()->GetPosition().Distance(player->GetPosition()) < 20.f) {
 //       if (GetOwner()->GetComponent<Enemy>()->GetCooldown() == 0.f) {
 //           GetOwner()->GetComponent<Enemy>()->Attack(player);
 //           GetOwner()->GetComponent<Enemy>()->SetCooldown(_delta_time);
 //       }
 //       else {
 //           GetOwner()->GetComponent<Enemy>()->SetCooldown(_delta_time);
 //           if (GetOwner()->GetComponent<Enemy>()->GetCooldown() >= GetOwner()->GetComponent<Enemy>()->GetAttackSpeed()) {
 //               GetOwner()->GetComponent<Enemy>()->SetCooldown(-GetOwner()->GetComponent<Enemy>()->GetCooldown());
 //           }
 //       }
 //   }
}