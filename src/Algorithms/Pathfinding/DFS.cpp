#include "visualizePathfinding.h"
#include <iostream>

bool dfs(Tile *currentTile,Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    if(currentTile->state!=TileState::source)
    {
        currentTile->setState(TileState::visited);
    }
    renderGrid(window);
    std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));

    std::vector<Tile*>neighbors;
    getNeighbors(*currentTile,neighbors,*gridObj);
    for(Tile* neighborTile:neighbors)
    {
        if(neighborTile->state==TileState::destination)
        {
            neighborTile->parentTile = currentTile;
            drawPath(gridObj,window,neighborTile->parentTile,config);
            return true;
        }


        if(neighborTile->state==notVisited)
        {
            neighborTile->parentTile = currentTile;

            if (dfs(neighborTile,gridObj,window,config)) {
                    return true;
            }

        }
    }
    return false;
}

void dfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    dfs(gridObj->srcTile,gridObj,window,config);
}
