#include "visualizePathfinding.h"
#include <iostream>

void bfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config){


    std::queue<Tile*> tilesQ;


    Tile *srcTile = &gridObj->grid[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    tilesQ.push(srcTile);
    while(!tilesQ.empty())
    {
        Tile* currentTile = tilesQ.front();
        tilesQ.pop();

        if(currentTile->state!=TileState::source)
        {
            currentTile->setState(TileState::visited);
        }


        std::vector<Tile*>neighbors;
        getNeighbors(*currentTile,neighbors,*gridObj);

        for(Tile* neighborTile:neighbors)
        {
            if(neighborTile->state==TileState::destination)
            {
                neighborTile->parentTile = currentTile;
                drawPath(gridObj,window,neighborTile->parentTile,config);
                return;
            }

            if(neighborTile->state==TileState::notVisited)
            {
                neighborTile->setState(TileState::inQueue);
                neighborTile->parentTile = currentTile;
                tilesQ.push(neighborTile);
            }
        }
        renderGrid(window);
        std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));

    }

}


