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
    gridObj->clearTilesCosts();
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

    while(!tilesPQ.empty())
    {
        Tile *currentTile = tilesPQ.top();
        tilesPQ.pop();

        if(currentTile->state!=TileState::source)
        {
            currentTile->setState(TileState::visited);
        }

        std::vector<Tile*>neighbors;
        getNeighbors(*currentTile,neighbors,*gridObj);

        for(Tile* neighborTile:neighbors)
        {
            if(neighborTile->state == TileState::destination)
            {
                neighborTile->parentTile = currentTile;
                drawPath(gridObj,window,neighborTile->parentTile,config);
                return;
            }

            if(neighborTile->state==TileState::notVisited)
            {
                neighborTile->setState(TileState::inQueue);
                neighborTile->parentTile = currentTile;
                tilesPQ.push(neighborTile);
            }

        }
        renderGrid(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));
    }

}
