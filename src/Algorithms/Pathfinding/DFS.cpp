#include "visualizePathfinding.h"
#include <iostream>

bool dfs(Vector2 currentTilePos,Grid *gridObj,std::vector<Vector2>*path,std::vector<std::vector<bool>>&visited)
{
    visited[currentTilePos.row][currentTilePos.col]=true;
    path->push_back(currentTilePos);
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


        if(!visited[new_row][new_col]&&newTile->state!=TileState::wall)
        {
            newTile->parentTile = &gridObj->grid[currentTilePos.row][currentTilePos.col];

            if (dfs(Vector2(new_col,new_row),gridObj,path,visited)) {
                    return true;
            }

        }
    }
    return false;
}

void dfsAlgorithm(Grid *gridObj,std::vector<Vector2>*path,bool &pathFound)
{
    std::vector<std::vector<bool>>visited(gridObj->gridSize,std::vector<bool>(gridObj->gridSize,0));
    pathFound= dfs(gridObj->sourceCoords,gridObj,path,visited);
}
