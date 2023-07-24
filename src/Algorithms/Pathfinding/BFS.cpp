#include "visualizePathfinding.h"
#include <iostream>

void bfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config){


    std::queue<Tile*> tilesQ;


    Tile *srcTile = &gridObj->grid[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    tilesQ.push(srcTile);
    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};
    while(!tilesQ.empty())
    {
        Tile* currentTile = tilesQ.front();
        tilesQ.pop();

        if(currentTile->state!=TileState::source)currentTile->state = TileState::visited;

        int currentCol = currentTile->pos.col;
        int currentRow = currentTile->pos.row;

        for(int i=0;i<4;i++)
        {
            int new_col = currentCol+dirX[i];
            int new_row = currentRow+dirY[i];

            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
            if(!isTileOnBoard||gridObj->grid[new_row][new_col].state==TileState::wall)continue;

            Tile *neighborTile = &gridObj->grid[new_row][new_col];

            if(neighborTile->state==TileState::destination)
            {
                neighborTile->parentTile = currentTile;
                drawPath(gridObj,window,neighborTile->parentTile,config);
                return;
            }


            if(neighborTile->state==TileState::notVisited)
            {
                neighborTile->state=TileState::inQueue;
                neighborTile->parentTile = currentTile;
                tilesQ.push(neighborTile);
            }
        }

        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));

    }

}


