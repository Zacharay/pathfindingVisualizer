#include "visualizePattern.h"
#include <vector>
#include <iostream>
void generateHamiltonian(Grid *gridObj,std::vector<Vector2> *walls);
void generateSpiral(bool isInnerSpiral,Grid *gridObj,std::vector<Vector2>*walls);

void visualizePattern(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    std::vector<Vector2> walls;

    if(config->selectedPattern==Patterns::HamiltonianCycle)
    {
        generateHamiltonian(gridObj,&walls);
    }
    else if(config->selectedPattern==Patterns::OuterSpiral)
    {
        generateSpiral(false,gridObj,&walls);
    }
    else if(config->selectedPattern==Patterns::InnerSpiral)
    {
        generateSpiral(true,gridObj,&walls);
    }

    for(int i=0;i<walls.size();i++)
    {
        Vector2 coords = walls[i];
        if( gridObj->grid[coords.row][coords.col].state!=TileState::destination&&
            gridObj->grid[coords.row][coords.col].state!=TileState::source)
        {
            gridObj->grid[coords.row][coords.col].state = TileState::wall;
        }


        if(i%config->substep==0)
        {
            renderGrid(gridObj,window);
            std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
        }
    }
    renderGrid(gridObj,window);
}
