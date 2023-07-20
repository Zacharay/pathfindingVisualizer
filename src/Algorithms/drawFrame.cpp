#include "drawFrame.h"
#include "../render.h"
#include <thread>
#include <chrono>
void drawFrame(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    for(int i=0;i<gridObj->gridSize;i++)
    {
        if( gridObj->grid[0][i].state==TileState::notVisited)
            gridObj->grid[0][i].state = TileState::wall;

        if( gridObj->grid[i][0].state==TileState::notVisited)
            gridObj->grid[i][0].state = TileState::wall;

        if(gridObj->grid[gridObj->gridSize-1][gridObj->gridSize-1-i].state == TileState::notVisited)
            gridObj->grid[gridObj->gridSize-1][gridObj->gridSize-1-i].state = TileState::wall;
        if(gridObj->grid[gridObj->gridSize-1-i][gridObj->gridSize-1].state == TileState::notVisited)
            gridObj->grid[gridObj->gridSize-1-i][gridObj->gridSize-1].state = TileState::wall;

        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
    }


}
