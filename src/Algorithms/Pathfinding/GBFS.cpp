#include "visualizePathfinding.h"
#include <vector>
#include <queue>
#include <iostream>
struct CompareNodesHCost {
    bool operator()(const Tile *tileA, const Tile *tileB) const {
        return tileA->hCost > tileB->hCost;
    }
};

void greedyBfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    for(int row=0;row<gridObj->gridSize;row++)
    {
        for(int col=0;col<gridObj->gridSize;col++)
        {
            gridObj->grid[row][col].calculateDistanceToDest(gridObj->destCoords);
        }
    }
    std::priority_queue<Tile*,std::vector<Tile*>,CompareNodesHCost>tilesPQ;
    Tile *srcTile = &gridObj->grid[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    tilesPQ.push(srcTile);

    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};
    while(!tilesPQ.empty())
    {
        Tile *currentTile = tilesPQ.top();
        tilesPQ.pop();

        if(currentTile->state!=TileState::source)currentTile->state = TileState::visited;

        for(int i=0;i<4;i++)
        {
            int new_col = currentTile->pos.col+dirX[i];
            int new_row = currentTile->pos.row+dirY[i];

            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
            if(!isTileOnBoard|| gridObj->grid[new_row][new_col].state == TileState::wall)continue;

            Tile *neighborTile = &gridObj->grid[new_row][new_col];

            if(neighborTile->state == TileState::destination)
            {
                neighborTile->parentTile = currentTile;
                drawPath(gridObj,window,neighborTile->parentTile,config);
                return;
            }

            if(neighborTile->state==TileState::notVisited)
            {
                neighborTile->state =TileState::inQueue;
                gridObj->grid[neighborTile->pos.row][neighborTile->pos.col].parentTile = currentTile;
                tilesPQ.push(neighborTile);
            }

        }
        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));
    }

}
