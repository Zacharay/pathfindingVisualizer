#include "visualizePathfinding.h"
#include <iostream>
bool BfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config){

    std::queue<Vector2> q;

    q.push(gridObj->sourceCoords);
    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};

    while(!q.empty())
    {
        Vector2 currentTilePos = q.front();
        q.pop();

        int parent_col = currentTilePos.col;
        int parent_row = currentTilePos.row;

        for(int i=0;i<4;i++)
        {
            int new_col = parent_col+dirX[i];
            int new_row = parent_row+dirY[i];

            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;;
            if(!isTileOnBoard)continue;

            Tile *newTile = &gridObj->grid[new_row][new_col];

            if(newTile->state==TileState::destination)
            {
                newTile->parentTile = &gridObj->grid[parent_row][parent_col];
                return true;
            }


            if(newTile->state==TileState::notVisited)
            {
                q.push(Vector2(new_col,new_row));
                newTile->state = TileState::visited;
                newTile->parentTile = &gridObj->grid[parent_row][parent_col];

            }
        }
        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
    }
    return false;
}
void visualizeBfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config){
    bool pathFound = BfsAlgorithm(gridObj,window,config);
    if(pathFound)
    {
            Tile *destParent = gridObj->grid[gridObj->destCoords.row][gridObj->destCoords.col].parentTile;
            drawPath(gridObj,window,destParent,config);
    }
}

