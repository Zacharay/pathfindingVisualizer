#include "drawPath.h"
#include "../render.h"
#include <thread>
#include <chrono>

void drawPath(Grid *gridObj,sf::RenderWindow *window,Tile *currentTile)
{
    while(currentTile->state!=TileState::source)
    {
        currentTile->state = TileState::active;
        currentTile = currentTile->parentTile;

        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}
