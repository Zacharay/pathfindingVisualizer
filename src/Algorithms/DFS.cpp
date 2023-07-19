#include "algorithms.h"
#include <iostream>

bool dfs(Vector2 currentTilePos,Grid *gridObj,sf::RenderWindow *window)
{
    int dirX[]= {1,0,-1,0};
    int dirY[]= {0,-1,0,1};

    for(int i=0;i<4;i++)
    {
        int new_col = currentTilePos.col + dirX[i];
        int new_row = currentTilePos.row + dirY[i];

        if(gridObj->grid[new_row][new_col].state==TileState::destination)
        {
            gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[currentTilePos.row][currentTilePos.col];
            return true;
        }

        if(new_col>=0&&new_col<gridObj->gridSize&&
            new_row>=0&&new_row<gridObj->gridSize&&
            gridObj->grid[new_row][new_col].state==TileState::notVisited)
        {
            gridObj->grid[new_row][new_col].state = TileState::visited;
            gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[currentTilePos.row][currentTilePos.col];

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            renderGrid(gridObj,window);

            if (dfs(Vector2(new_col,new_row),gridObj, window)) {
                    // Path found!
                    return true;
            }

        }
    }
    return false;
}

void visualizeDfs(Grid *gridObj,sf::RenderWindow *window)
{
    bool pathFound = dfs(gridObj->sourceCoords,gridObj,window);
    if(pathFound)
    {
        Tile *destParent = gridObj->grid[gridObj->destCoords.row][gridObj->destCoords.col].parentTile;
        drawPath(gridObj,window,destParent);
    }
}
