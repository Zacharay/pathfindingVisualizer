#pragma once
#include "Vector2.h"
#include "Tile.h"
class Grid
{
public:
    static const int gridSize = 50;
    Tile grid[gridSize][gridSize];
    Vector2 sourceCoords;
    Vector2 destCoords;
    int tileSize;
public:
    Grid(int windowSize);
};
