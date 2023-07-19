#pragma once
#include "Vector2.h"
#include "Tile.h"
class Grid
{
public:
    int gridSize = 50;
    Tile **grid;
    Vector2 sourceCoords;
    Vector2 destCoords;
    int tileSize;
public:
    Grid(int windowSize);
    ~Grid();
    void resizeGrid(int newGridSize,int windowSize);
};
