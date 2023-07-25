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
    Tile *srcTile;
    Tile *destTile;
    int tileSize;
public:
    Grid(int windowSize);
    ~Grid();
    void resizeGrid(int newGridSize,int windowSize,CONFIG &config);
    void clearWalls();
    void clearTilesCosts();
    void clearPath();
private:
    void setNewSourceAndDest();
};
