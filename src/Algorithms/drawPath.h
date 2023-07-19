#pragma once
#include "SFML/Graphics.hpp"
#include "../Grid/Grid.h"
#include "../config.h"

void drawPath(Grid *gridObj,sf::RenderWindow *window,Tile *currentTile,CONFIG *config);
