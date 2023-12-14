#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#include "Component.h"
#include "Components/TileMap.h"

class PathFinding : public Component
{
public:
    PathFinding(const TileMap& _tilemap) : tilemap(_tilemap) {};

private:
    const TileMap& tilemap;
    Maths::Vector2f target;
    std::deque<Maths::Vector2f> path;
};