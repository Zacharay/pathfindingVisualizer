#include "Grid.h"
#include <iostream>
Grid::Grid(int windowSize)
:sourceCoords(10,20),destCoords(30,20)
{
    tileSize = windowSize/gridSize;
    grid[sourceCoords.row][sourceCoords.col].state = source;
    grid[destCoords.row][destCoords.col].state = destination;
}

