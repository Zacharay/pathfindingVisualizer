#include "algorithms.h"
#include <vector>
#include <random>
#include <iostream>
//Disjoint Union Set for cycle detection
int findDSU(int a,int *rep)
{
    if(rep[a]==a)return a;
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
int convertCoordsToIndex(Vector2 coords,int nodesPerRow)
{
    return coords.col + coords.row*nodesPerRow;
}

void kruskalMst(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,std::vector<Vector2>*walls)
{
    int nodesPerRow = gridObj->gridSize-2;
    int *rep = new int[nodesPerRow*nodesPerRow];
    for(int i=0;i<nodesPerRow*nodesPerRow;i++)
    {
        rep[i]= i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(walls->begin(), walls->end(), gen);

    int dirX[] = {0,0,2,-2};
    int dirY[] = {2,-2,0,0};
    while(!walls->empty())
    {
        Vector2 parentTile = walls->back();
        walls->pop_back();

        int idx = convertCoordsToIndex(parentTile,nodesPerRow);
        //std::cout<<idx<<std::endl;
        int parent_rep = findDSU(idx,rep);
        for(int i=0;i<4;i++)
        {
            int new_row = parentTile.row + dirY[i];
            int new_col = parentTile.col + dirX[i];

            bool isTileOnBoard = new_col>0&&new_col<nodesPerRow&&new_row>0&&new_row<nodesPerRow;
            if(!isTileOnBoard)continue;

            int nbr_idx = convertCoordsToIndex(Vector2(new_col,new_row),nodesPerRow);
            int nbr_rep = findDSU(nbr_idx,rep);

            if(nbr_rep!=parent_rep)
            {

                unionDSU(nbr_rep,parent_rep,rep);
                if(dirX[i]==2)
                {
                    gridObj->grid[parentTile.row][parentTile.col+1].state = TileState::wall;
                }
                else if(dirX[i]==-2)
                {
                    gridObj->grid[parentTile.row][parentTile.col-1].state = TileState::wall;
                }
                else if(dirY[i]==2)
                {
                    gridObj->grid[parentTile.row+1][parentTile.col].state = TileState::wall;
                }
                else if(dirY[i]==-2)
                {
                    gridObj->grid[parentTile.row-1][parentTile.col].state = TileState::wall;
                }
                renderGrid(gridObj,window);
                std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
            }
        }


    }
    delete []rep;
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
    kruskalMst(gridObj,window,config,&walls);

};
