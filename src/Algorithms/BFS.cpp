#pragma once
#include "../Grid/Grid.h"
#include "queue"
#include "../Grid/Vector2.h"
#include "../render.h"
#include <chrono>
#include <thread>

void visualizeBfs(Grid *gridObj,sf::RenderWindow *window){

    std::queue<Vector2> q;

    q.push(gridObj->sourceCoords);

    bool pathFound = false;

    while(!q.empty()&&!pathFound)
    {
        Vector2 currentTile = q.front();
        q.pop();
        int dirX[] = {0,0,1,-1};
        int dirY[] = {1,-1,0,0};

        int parent_col = currentTile.col;
        int parent_row = currentTile.row;

        for(int i=0;i<4;i++)
        {
            int new_col = parent_col+dirX[i];
            int new_row = parent_row+dirY[i];


            if(new_col == gridObj->destCoords.col&&new_row==gridObj->destCoords.row)
            {
                pathFound=true;
                break;
            }

            if(new_col>=0&&new_col<gridObj->gridSize&&
               new_row>=0&&new_row<gridObj->gridSize&&
               gridObj->grid[new_row][new_col].state==TileState::notVisited)
            {
                q.push(Vector2(new_col,new_row));
                gridObj->grid[new_row][new_col].state = TileState::visited;
                gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[parent_row][parent_col];

            }
        }


        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
}
void reconstructPath(Grid *gridObj,sf::RenderWindow *window)
{

}
