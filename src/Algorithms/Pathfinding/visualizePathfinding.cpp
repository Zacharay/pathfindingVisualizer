#include "visualizePathfinding.h"

void bfsAlgorithm(Grid *gridObj,std::vector<Vector2>*path,bool &pathFound);
void dfsAlgorithm(Grid *gridObj,std::vector<Vector2>*path,bool &pathFound);
void astarAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void greedyBfsAlgorithm(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);

void visualizePathfinding(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    bool pathFound = false;
    if(config->selectedAlgorithm==Algorithms::BFS)
    {
        //bfsAlgorithm(gridObj,&path,pathFound);
    }
    else if(config->selectedAlgorithm==Algorithms::DFS)
    {
        //dfsAlgorithm(gridObj,&path,pathFound);
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
