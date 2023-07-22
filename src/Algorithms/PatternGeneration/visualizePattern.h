#pragma once
#include "../../Grid/Grid.h"
#include "queue"
#include "../../Grid/Vector2.h"
#include "../../render.h"
#include <chrono>
#include <thread>
#include "../Others/generateFrame.h"
#include <SFML/Graphics.hpp>
#include "../../config.h"

enum Patterns{
    KruskalMaze,
    PrimMaze,
    OuterSpiral,
    InnerSpiral,
};

void visualizePattern(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
