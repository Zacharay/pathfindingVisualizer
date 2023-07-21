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
enum Algorithms{
    BFS,
    DFS
};
void visualizePathfinding(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
