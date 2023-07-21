#pragma once

#include "../Grid/Grid.h"
#include "queue"
#include "../Grid/Vector2.h"
#include "../render.h"
#include <chrono>
#include <thread>
#include "drawPath.h"
#include <SFML/Graphics.hpp>
#include "../config.h"

void visualizeBfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void visualizeDfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void visualizeHamiltonian(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void visualizeSpiral(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,bool innerSpiral);
