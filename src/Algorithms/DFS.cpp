#include "algorithms.h"
#include <iostream>

bool dfs(Vector2 currentTilePos,Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    int dirX[]= {1,0,-1,0};
    int dirY[]= {0,-1,0,1};

    for(int i=0;i<4;i++)
    {
        int new_col = currentTilePos.col + dirX[i];
        int new_row = currentTilePos.row + dirY[i];


        bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
        if(!isTileOnBoard)continue;

        Tile *newTile = &gridObj->grid[new_row][new_col];

        if(newTile->state==TileState::destination)
        {
            newTile->parentTile = &gridObj->grid[currentTilePos.row][currentTilePos.col];
            return true;
        }


        if(newTile->state==TileState::notVisited)
        {
            newTile->state = TileState::visited;
            newTile->parentTile = &gridObj->grid[currentTilePos.row][currentTilePos.col];

            std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
            renderGrid(gridObj,window);

            if (dfs(Vector2(new_col,new_row),gridObj, window,config)) {
                    // Path was found!
                    return true;
            }

        }
    }
    return false;
}

void visualizeDfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    bool pathFound = dfs(gridObj->sourceCoords,gridObj,window,config);
    if(pathFound)
    {
            Tile *destParent = gridObj->grid[gridObj->destCoords.row][gridObj->destCoords.col].parentTile;
            drawPath(gridObj,window,destParent,config);
    }
}
