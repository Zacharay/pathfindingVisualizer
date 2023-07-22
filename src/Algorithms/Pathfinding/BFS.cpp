#include "visualizePathfinding.h"
#include <iostream>
bool bfsAlgorithm(Grid *gridObj,std::vector<Vector2>*path){

    std::queue<Vector2> q;
    bool **visited;
    visited = new bool*[gridObj->gridSize];
    for(int i=0;i<gridObj->gridSize;i++)
    {
        visited[i] = new bool[gridObj->gridSize]{0};
    }

    q.push(gridObj->sourceCoords);
    visited[gridObj->sourceCoords.row][gridObj->sourceCoords.col]=1;
    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};

    while(!q.empty())
    {
        Vector2 currentTilePos = q.front();
        path->push_back(currentTilePos);
        q.pop();

        int parent_col = currentTilePos.col;
        int parent_row = currentTilePos.row;

        for(int i=0;i<4;i++)
        {
            int new_col = parent_col+dirX[i];
            int new_row = parent_row+dirY[i];

            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
            if(!isTileOnBoard)continue;

            Tile *newTile = &gridObj->grid[new_row][new_col];

            if(newTile->state==TileState::destination)
            {
                newTile->parentTile = &gridObj->grid[parent_row][parent_col];
                return true;
            }


            if(!visited[new_row][new_col]&&gridObj->grid[new_row][new_col].state!=TileState::wall)
            {
                q.push(Vector2(new_col,new_row));
                visited[new_row][new_col]=1;
                newTile->parentTile = &gridObj->grid[parent_row][parent_col];

            }
        }
    }
    return false;
}

