#include "algorithms.h"
#include <vector>
#include <random>
#include <iostream>
//Disjoint Union Set for cycle detection
int findDSU(int a,int *rep)
{
    if(rep[a]==-1)return a;
    else return rep[a]=findDSU(rep[a],rep);
}
void unionDSU(int a,int b, int *rep)
{
    int repA = findDSU(a,rep);
    int repB = findDSU(b,rep);
    if(repA!=repB)
    {
        rep[repA]=repB;
    }
}
void kruskalMst(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,std::vector<Vector2>*walls)
{
    int nodesPerRow = gridObj->gridSize-2;
    int rep[nodesPerRow*nodesPerRow];
    for(int i=0;i<nodesPerRow*nodesPerRow;i++)
    {
        rep[i]= i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(walls->begin(), walls->end(), gen);
    while(!walls.empty())
    {
        //do kruskal logic
    }
}

void drawFrame(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    for(int i=0;i<gridObj->gridSize;i++)
    {
        gridObj->grid[0][i].state = TileState::wall;

        gridObj->grid[i][0].state = TileState::wall;

        renderGrid(gridObj,window);


        gridObj->grid[gridObj->gridSize-1][gridObj->gridSize-1-i].state = TileState::wall;
        gridObj->grid[gridObj->gridSize-1-i][gridObj->gridSize-1].state = TileState::wall;
        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
    }


}
void drawInitialTiles(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,std::vector<Vector2>*walls)
{
    for(int y = 2;y<gridObj->gridSize-2;y+=2)
    for(int x=2;x<gridObj->gridSize-2;x+=2)
    {
        gridObj->grid[y][x].state = TileState::wall;
        walls->push_back(Vector2(x,y));
        renderGrid(gridObj,window);
        std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
    }
}



void visualizeHamiltonian(Grid *gridObj,sf::RenderWindow *window,CONFIG *config)
{
    std::vector<Vector2>walls;

    drawFrame(gridObj,window,config);
    drawInitialTiles(gridObj,window,config,&walls);
    kruskalMst(gridObj,window,config,&walls)

};
