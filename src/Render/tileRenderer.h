#pragma once
#include "../Grid/Grid.h"
#include "SFML/Graphics.hpp"
#include "../config.h"

void initializeTileColors();
void initializeGridTexture(const CONFIG& config,const Grid &gridObj);
void renderGrid(Grid *gridObj,sf::RenderWindow *window);
void updateTile(const Tile &tile,const Grid &gridObj);
