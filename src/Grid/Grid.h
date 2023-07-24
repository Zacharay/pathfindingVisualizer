#pragma once
#include "Vector2.h"
#include "Tile.h"
#include "../config.h"
#include <vector>
class Grid
{
public:
    int gridSize = 45;
    Tile **grid;
    Vector2 sourceCoords;
    Vector2 destCoords;
    int tileSize;
public:
    Grid(int windowSize);
    ~Grid();
    void resizeGrid(int newGridSize,int windowSize,CONFIG &config);
    void clearWalls();
    void clearPath();
};
