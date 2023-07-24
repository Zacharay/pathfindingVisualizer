#include "visualizePathfinding.h"

void bfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void dfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void astarAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void greedyBfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);

void visualizePathfinding(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{

    if(config->selectedAlgorithm==Algorithms::BFS)
    {
        bfsAlgorithm(gridObj,window,config);
    }
    else if(config->selectedAlgorithm==Algorithms::DFS)
    {
        dfsAlgorithm(gridObj,window,config);
    }
    else if(config->selectedAlgorithm==Algorithms::aStar)
    {
        astarAlgorithm(gridObj,window,config);
    }
    else if(config->selectedAlgorithm==Algorithms::GBFS)
    {
        greedyBfsAlgorithm(gridObj,window,config);
    }
}
