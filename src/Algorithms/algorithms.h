#pragma once

#include "../Grid/Grid.h"
#include "queue"
#include "../Grid/Vector2.h"
#include "../render.h"
#include <chrono>
#include <thread>
#include "drawPath.h"
#include <SFML/Graphics.hpp>

void visualizeBfs(Grid *gridObj,sf::RenderWindow *window);
void visualizeDfs(Grid *gridObj,sf::RenderWindow *window);
