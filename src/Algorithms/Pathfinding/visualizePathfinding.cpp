#include "visualizePathfinding.h"

bool bfsAlgorithm(Grid *gridObj,std::vector<Vector2>*path);
bool dfsAlgorithm(Grid *gridObj,std::vector<Vector2>*path);
void astarAlgorithm(Grid *gridObj,std::vector<Vector2>*path,bool &pathFound);

void visualizePathfinding(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    std::vector<Vector2>path;
    bool pathFound = false;
    if(config->selectedAlgorithm==Algorithms::BFS)
    {
        pathFound = bfsAlgorithm(gridObj,&path);
    }
    else if(config->selectedAlgorithm==Algorithms::DFS)
    {
        pathFound = dfsAlgorithm(gridObj,&path);
    }
    else if(config->selectedAlgorithm==Algorithms::aStar)
    {
        astarAlgorithm(gridObj,&path,pathFound);
    }
    for(int i=0;i<path.size();i++)
    {
        Vector2 coords = path[i];
        if( gridObj->grid[coords.row][coords.col].state!=TileState::destination&&
            gridObj->grid[coords.row][coords.col].state!=TileState::source)
        {
            gridObj->grid[coords.row][coords.col].state= TileState::visited;
        }


        if(i%config->substep==0)
        {
            renderGrid(gridObj,window);
            std::this_thread::sleep_for(std::chrono::milliseconds(11-config->visualizationSpeed));
        }
    }

    if(pathFound){
        Tile *destParent = gridObj->grid[gridObj->destCoords.row][gridObj->destCoords.col].parentTile;
        drawPath(gridObj,window,destParent,config);
    }
}
