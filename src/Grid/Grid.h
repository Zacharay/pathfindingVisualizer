#pragma once
#include <vector>
#include "Tile.h"
class Grid
{
public:
    static const int gridSize = 50;
    Tile grid[gridSize][gridSize];
    int tileSize;
public:
    Grid(int windowSize);
};
