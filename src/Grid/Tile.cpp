#include "Tile.h"
#include "Vector2.h"
#include "math.h"
#include "../Render/tileRenderer.h"
#include <iostream>

void Tile::calculateDistanceToDest(Vector2 destCoords)
{
    int dist = std::abs(pos.col-destCoords.col)+std::abs(pos.row-destCoords.row);
    hCost = dist;
}
void Tile::setState(int newState)
{
    state = newState;
    updateTile(*this);
}
