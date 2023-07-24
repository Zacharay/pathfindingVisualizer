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
    pos(0,0),state(TileState::notVisited),hCost(0),gCost(1000),fCost(0){}
    Tile(int row,int col):
    pos(col,row),state(TileState::notVisited),hCost(0),gCost(1000),fCost(0){}
    void calculateDistanceToDest(Vector2 destCoords);
};
