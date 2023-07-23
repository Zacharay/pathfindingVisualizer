#pragma once
#include "Vector2.h"
enum TileState
{
    notVisited,
    inQueue,
    visited,
    path,
    wall,
    source,
    destination
};
struct Tile
{
    Vector2 pos;
    int state;
    int hCost;
    int gCost;
    int fCost;

    Tile *parentTile = nullptr;
    Tile():
    pos(0,0),fCost(0),gCost(1000),hCost(0),state(TileState::notVisited){}
    Tile(int row,int col):
    pos(col,row),fCost(0),gCost(1000),hCost(0),state(TileState::notVisited){}
    void calculateDistanceToDest(Vector2 destCoords);
};
