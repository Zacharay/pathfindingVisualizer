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
    int tileSize;

    Tile *parentTile = nullptr;
    Tile():
    pos(0,0),state(TileState::notVisited),hCost(0),gCost(1000),fCost(0),tileSize(18){}
    Tile(int row,int col,int tileSize):
    pos(col,row),state(TileState::notVisited),hCost(0),gCost(1000),fCost(0),tileSize(tileSize){}
    void calculateDistanceToDest(Vector2 destCoords);
    void setState(int newState);
    void setInitialCosts();
};
