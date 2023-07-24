#pragma once
#include "../../Grid/Grid.h"
#include "queue"
#include "../../Grid/Vector2.h"
#include "../../render.h"
#include <chrono>
#include <thread>
#include "../Others/drawPath.h"
#include <SFML/Graphics.hpp>
#include "../../config.h"
#include "../Others/getNeighbors.h"
enum Algorithms{
    BFS,
    DFS,
    aStar,
    GBFS
};
void visualizePathfinding(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
