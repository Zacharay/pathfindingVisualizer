#include "visualizePattern.h"
#include <vector>
#include <iostream>
void generateHamiltonian(Grid *gridObj,std::vector<Vector2> *walls);
void visualizeSpiral(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,bool innerSpiral);

void visualizePattern(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    std::vector<Vector2> walls;

    if(config->selectedPattern==Patterns::HamiltonianCycle)
    {
        generateHamiltonian(gridObj,&walls);
    }

    for(int i=0;i<walls.size();i++)
    {
        Vector2 coords = walls[i];
        gridObj->grid[coords.row][coords.col].state = TileState::wall;

        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
    }

}
