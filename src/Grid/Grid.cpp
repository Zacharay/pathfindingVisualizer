#include "Grid.h"
#include <iostream>
Grid::Grid(int windowSize)
:sourceCoords(5,5),destCoords(5,8)
{
    grid = new Tile*[gridSize];
    for(int i=0;i<gridSize;i++)
    {
        grid[i] = new Tile[gridSize];
    }

    tileSize = windowSize/gridSize;
    grid[sourceCoords.row][sourceCoords.col].state = source;
    grid[destCoords.row][destCoords.col].state = destination;
}
Grid::~Grid()
{
    for (int i = 0; i < gridSize; ++i)
    {
      delete[] grid[i];
    }

    delete[] grid;

}

int roundToDecimal5(int number) {
    int remainder = number % 10;
    int roundedNumber;

    if (remainder <= 2)
        roundedNumber = number - remainder;
    else if (remainder >= 8)
        roundedNumber = number + (10 - remainder);
    else
        roundedNumber = number + (5 - remainder);

    return roundedNumber;
}

void Grid::resizeGrid(int newGridSize,int windowSize)
{
    Tile** newGrid = new Tile*[newGridSize];
    for (int i = 0; i < newGridSize; ++i) {
      newGrid[i] = new Tile[newGridSize];
    }

    int copySize = (newGridSize<gridSize)?newGridSize:gridSize;

    for(int i=0;i<copySize;i++)
    {
        for(int j=0;j<copySize;j++)
        {
            newGrid[i][j] = grid[i][j];
        }
    }

    for (int i = 0; i < gridSize; ++i) {
      delete[] grid[i];
    }
    delete[] grid;

    gridSize = newGridSize;
    grid = newGrid;
    tileSize = windowSize/gridSize;
}

