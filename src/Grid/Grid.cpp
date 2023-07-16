#include "Grid.h"
#include <iostream>
Grid::Grid(int windowSize)
:sourceCoords(10,24),destCoords(49,25)
{
    tileSize = windowSize/gridSize;
    grid[sourceCoords.row][sourceCoords.col].state = source;
    grid[destCoords.row][destCoords.col].state = destination;
}

