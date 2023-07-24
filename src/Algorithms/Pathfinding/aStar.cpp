#include "visualizePathfinding.h"
#include <queue>


struct CompareNodesFCost {
    bool operator()(const Tile *tileA, const Tile *tileB) const {
        return tileA->fCost > tileB->fCost;
    }
};

void astarAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{

    for(int row=0;row<gridObj->gridSize;row++)
    {
        for(int col=0;col<gridObj->gridSize;col++)
        {
            gridObj->grid[row][col].calculateDistanceToDest(gridObj->destCoords);
        }
    }

    std::priority_queue<Tile*,std::vector<Tile*>,CompareNodesFCost>tilesPQ;

    Tile *srcTile = &gridObj->grid[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    srcTile->fCost = srcTile->hCost;
    srcTile->gCost = 0;
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

            if(neighborTile->state!=TileState::visited)
            {

                int tentativeG = currentTile->gCost +1;
                if(tentativeG < neighborTile->gCost)
                {
                     neighborTile->gCost = tentativeG;
                     neighborTile->fCost =neighborTile->gCost  + neighborTile->hCost;
                     neighborTile->parentTile = currentTile;
                     if(neighborTile->state!= TileState::inQueue)
                     {
                        neighborTile->setState(TileState::inQueue);
                        tilesPQ.push(neighborTile);
                     }
                }
            }

        }
        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));
    }
}
