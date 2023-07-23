#include "Tile.h"
#include "Vector2.h"
#include "math.h"
void Tile::calculateDistanceToDest(Vector2 destCoords)
{
    int dist = std::abs(pos.col-destCoords.col)+std::abs(pos.row-destCoords.row);
    hCost = dist;
}
