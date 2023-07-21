#include "drawPath.h"
#include "../../render.h"
#include <thread>
#include <chrono>
#include <vector>

void drawPath(Grid *gridObj,sf::RenderWindow *window,Tile *currentTile,CONFIG *config)
{
    std::vector<Tile*>path;
    while(currentTile->state!=TileState::source)
    {
        path.push_back(currentTile);
        currentTile = currentTile->parentTile;
    }

    for(int i=path.size()-1;i>=0;i--)
    {
        path[i]->state = TileState::path;
        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(std::max(5,101-config->visualizationSpeed)));

    }
}