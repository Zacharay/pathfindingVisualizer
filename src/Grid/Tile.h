#pragma once
enum TileState
{
    notVisited,
    visited,
    active,
    wall,
    source,
    destination
};
struct Tile
{
    int state = active;
};
