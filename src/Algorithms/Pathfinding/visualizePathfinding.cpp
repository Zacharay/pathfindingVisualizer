#include "visualizePathfinding.h"

void visualizeBfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);
void visualizeDfs(Grid *gridObj,sf::RenderWindow *window,CONFIG *config);

void visualizePathfinding(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    switch(config->selectedPattern)
    {
        case Algorithms::BFS:
            break;
        case Algorithms::DFS:
            break;
    }
}
