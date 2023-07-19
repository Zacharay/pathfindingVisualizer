#pragma once
enum TileState
{
    notVisited,
    visited,
    path,
    wall,
    source,
    destination
};
struct Tile
{
    int state = notVisited;
    Tile *parentTile = nullptr;
};
