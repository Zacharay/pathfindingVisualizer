#include "Grid.h"
#include "../Render/tileRenderer.h"
#include "iostream"
Grid::Grid(int windowSize)
{
    tileSize = windowSize/gridSize;
    grid = new Tile*[gridSize];
    for(int i=0;i<gridSize;i++)
    {
        grid[i]= new Tile[gridSize];
    }


    for(int row=0;row<gridSize;row++)
        for(int col = 0 ;col<gridSize;col++)
            grid[row][col] = Tile(row,col,tileSize);

    setNewSourceAndDest();
}
Grid::~Grid()
{
    for(int i=0;i<gridSize;i++)
        delete [] grid[i];
    delete [] grid;
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
void Grid::setNewSourceAndDest()
{
    int srcRow = gridSize/2;
    int srcCol = gridSize/10;
    srcTile = &grid[srcRow][srcCol];
    srcTile->setState(TileState::source);

    int destRow = gridSize/2;
    int destCol = gridSize-(gridSize/10);
    destTile = &grid[destRow][destCol];
    destTile->setState(TileState::destination);
}
void Grid::resizeGrid(int newGridSize,int windowSize,CONFIG &config)
{

    for (int i = 0; i < gridSize; ++i) {
      delete[] grid[i];
    }
    delete[] grid;

    tileSize = windowSize/newGridSize;
    gridSize = newGridSize;


    grid = new Tile*[newGridSize];
    for (int i = 0; i < newGridSize; ++i) {
      grid[i] = new Tile[newGridSize];
    }

    for(int row=0;row<newGridSize;row++)
        for(int col = 0 ;col<newGridSize;col++)
            {
                grid[row][col] = Tile(row,col,tileSize);
                grid[row][col].setState(TileState::notVisited);
            }
    setNewSourceAndDest();

}
void Grid::clearTilesCosts()
{
    for(int row=0;row<gridSize;row++)
    {
        for(int col=0;col<gridSize;col++)
        {
            grid[row][col].setInitialCosts();
        }
    }
}

void Grid::clearWalls()
{
    for(int row=0;row<gridSize;row++)
    {
        for(int col=0;col<gridSize;col++)
        {
            if(grid[row][col].state==TileState::wall)
            {
                grid[row][col].setState(TileState::notVisited);
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
            if(grid[row][col].state==TileState::visited||grid[row][col].state==TileState::path||grid[row][col].state==TileState::inQueue)
            {
                grid[row][col].setState(TileState::notVisited);
            }
        }
    }
}
