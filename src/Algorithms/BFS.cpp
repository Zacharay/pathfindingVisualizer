#include "algorithms.h"
void visualizeBfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config){

    std::queue<Vector2> q;

    q.push(gridObj->sourceCoords);

    bool pathFound = false;
    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};

    while(!q.empty()&&!pathFound)
    {
        Vector2 currentTile = q.front();
        q.pop();

        int parent_col = currentTile.col;
        int parent_row = currentTile.row;

        for(int i=0;i<4;i++)
        {
            int new_col = parent_col+dirX[i];
            int new_row = parent_row+dirY[i];

            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;;
            if(!isTileOnBoard)continue;

            if(gridObj->grid[new_row][new_col].state==TileState::destination);
            {
                pathFound=true;
                //gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[parent_row][parent_col];
                //break;
            }

            if(gridObj->grid[new_row][new_col].state==TileState::notVisited)
            {
                q.push(Vector2(new_col,new_row));
                gridObj->grid[new_row][new_col].state = TileState::visited;
                gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[parent_row][parent_col];

            }
        }


        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
    }
    if(pathFound)
    {
            Tile *destParent = gridObj->grid[gridObj->destCoords.row][gridObj->destCoords.col].parentTile;
            drawPath(gridObj,window,destParent,config);
    }
}

