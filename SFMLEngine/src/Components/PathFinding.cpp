#include <cmath>
#include <algorithm>
#include <unordered_set>
#include "Components/PathFinding.h"

std::vector<Node> PathFinding::FindPath(std::vector<SquareCollider*> obstacles, Maths::Vector2f start, Maths::Vector2f end) {
	Node startNode(start), endNode(end);
	std::list<Node> openList;
	std::list<Node> closedList;

	openList.push_back(startNode);

	int maxIterations = 10000; // Limite pour prévenir les boucles infinies

	while (!openList.empty() && maxIterations > 0) {
		auto it = std::min_element(openList.begin(), openList.end(), [](const Node& a, const Node& b) {
			return a.F() < b.F();
			});
		Node current = *it;

		std::cout << "Current Node: " << current.x << ", " << current.y << std::endl;

		if (current == endNode) {
			std::cout << "Reached the end node." << std::endl;
			std::vector<Node> path;
			while (current.parent) {
				path.push_back(current);
				current = *current.parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}

		openList.erase(it);
		closedList.push_back(current);

		for (int dx = -32; dx <= 32; dx += 32) {
			for (int dy = -32; dy <= 32; dy += 32) {
				if (dx == 0 && dy == 0) continue;

				Node neighbor(current.x + dx, current.y + dy, &current);

				if (isColliding(obstacles, neighbor.x, neighbor.y)) continue;
				if (std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end()) continue;

				neighbor.G = current.G + (dx == 0 || dy == 0 ? 32 : 45);
				neighbor.H = heuristic(neighbor, endNode);

				auto openIt = std::find(openList.begin(), openList.end(), neighbor);
				if (openIt != openList.end() && openIt->G <= neighbor.G) continue;

				openList.push_back(neighbor);
			}
		}

		maxIterations--;
		if (maxIterations == 0) {
			std::cout << "Max iterations reached. Possible infinite loop detected." << std::endl;
		}
	}

	std::cout << "Path not found or max iterations reached." << std::endl;
	return {}; // Return an empty path if no path is found or if max iterations reached
}

void PathFinding::Update(float _delta_time) {
	if (!path.empty()) {
		Maths::Vector2f entityPosition = GetOwner()->GetPosition(); // Position initiale de l'entité
		const Node& nextNode = path.front(); // Premier Node du chemin

		// Position de la prochaine étape sur le chemin
		Maths::Vector2f nextPosition(nextNode.x, nextNode.y);

		// Interpolation linéaire pour un mouvement fluide
		float lerpFactor = 0.1f; // Ajustez ce facteur pour la vitesse de déplacement
		entityPosition.x += (nextPosition.x - entityPosition.x) * lerpFactor * _delta_time;
		entityPosition.y += (nextPosition.y - entityPosition.y) * lerpFactor * _delta_time;

		// Vérifier si l'entité a atteint la position suivante
		float threshold = 5.0f; // Seuil de distance pour considérer la position comme atteinte
		if ((entityPosition - nextPosition).Magnitude() < threshold) {
			path.erase(path.begin()); // Retirer le Node actuel du chemin
		}

		// Mettre à jour la position de l'entité
		GetOwner()->SetPosition(entityPosition);
	}
}