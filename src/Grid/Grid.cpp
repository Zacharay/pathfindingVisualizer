#include "Grid.h"
#include <iostream>
Grid::Grid(int windowSize)
:sourceCoords(24,24),destCoords(10,5)
{
    grid = new Tile*[gridSize];
    for(int i=0;i<gridSize;i++)
    {
        grid[i] = new Tile[gridSize];
    }

    for(int row=0;row<gridSize;row++)
        for(int col = 0 ;col<gridSize;col++)
            grid[row][col] = Tile(row,col);

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

    for(int row=0;row<newGridSize;row++)
        for(int col = 0 ;col<newGridSize;col++)
            newGrid[row][col] = Tile(row,col);

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
void Grid::clearWalls()
{
    for(int row=0;row<gridSize;row++)
    {
        for(int col=0;col<gridSize;col++)
        {
            if(grid[row][col].state==TileState::wall)
            {
                grid[row][col].state = TileState::notVisited;
            }
        }
    }
}
void Grid::clearPath()
{
    for(int row=0;row<gridSize;row++)
    {
        for(int col=0;col<gridSize;col++)
        {
            if(grid[row][col].state==TileState::visited||grid[row][col].state==TileState::path)
            {
                grid[row][col].state = TileState::notVisited;
            }
        }
    }
}
