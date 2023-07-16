#pragma once
#include "../Grid/Grid.h"
#include "queue"
#include "../Grid/Vector2.h"
#include <iostream>

bool bfsIteration(std::queue<Vector2> *q,Grid *gridObj)
{
    Vector2 currentTile = q->front();
    q->pop();
    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};

    int parent_x = currentTile.col;
    int parent_y = currentTile.row;

    for(int i=0;i<4;i++)
    {
        int new_x = parent_x+dirX[i];
        int new_y = parent_y+dirY[i];


        if(new_x == gridObj->destCoords.col&&new_y==gridObj->destCoords.row)
        {
            return true;
        }

        if(new_x>=0&&new_x<gridObj->gridSize&&
           new_y>=0&&new_y<gridObj->gridSize&&
           gridObj->grid[new_y][new_x].state==TileState::notVisited)
        {
            q->push(Vector2(new_x,new_y));
            gridObj->grid[new_y][new_x].state = TileState::visited;

        }
    }
    return false;
}

void visualizeBfs(Grid *gridObj){

    std::queue<Vector2> q;

    q.push(gridObj->sourceCoords);
    /*for(int i=0;i<100;i++)
    {
        bfsIteration(&q,gridObj);
    }*/
    while(!q.empty())
    {
        if(bfsIteration(&q,gridObj))
        {
            break;
        }
    }
}
