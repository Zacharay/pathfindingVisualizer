#include "visualizePathfinding.h"
#include <iostream>

bool dfs(Tile *currentTile,Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    if(currentTile->state!=TileState::source)currentTile->state = TileState::visited;
    renderGrid(gridObj,window);
    std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));

    int dirX[]= {1,0,-1,0};
    int dirY[]= {0,-1,0,1};

    for(int i=0;i<4;i++)
    {
        int new_col = currentTile->pos.col + dirX[i];
        int new_row = currentTile->pos.row + dirY[i];


        bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
        if(!isTileOnBoard)continue;

        Tile *newTile = &gridObj->grid[new_row][new_col];

        if(newTile->state==TileState::destination)
        {
            newTile->parentTile = &gridObj->grid[currentTile->pos.row][currentTile->pos.col];
            drawPath(gridObj,window,newTile->parentTile,config);
            return true;
        }


        if(newTile->state==notVisited&&newTile->state!=TileState::wall)
        {
            newTile->parentTile = &gridObj->grid[currentTile->pos.row][currentTile->pos.col];

            if (dfs(newTile,gridObj,window,config)) {
                    return true;
            }

        }
    }
    return false;
}

void dfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    Tile *srcTile = &gridObj->grid[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    bool pathFound= dfs(srcTile,gridObj,window,config);
}
