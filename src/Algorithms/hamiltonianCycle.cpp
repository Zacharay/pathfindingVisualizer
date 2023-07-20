#include "algorithms.h"
#include <vector>
#include <random>
#include <iostream>
#include "drawFrame.h"


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

    std::vector<int>randomOrder = {0,1,2,3};
    int dirX[] = {0,0,2,-2};
    int dirY[] = {2,-2,0,0};
    while(!walls->empty())
    {
        Vector2 parentTile = walls->back();
        walls->pop_back();

        int parentIdx = convertCoordsToIndex(parentTile,nodesPerRow);
        int parentRep = findDSU(parentIdx,rep);
        std::shuffle(randomOrder.begin(),randomOrder.end(),gen);
        for(int i=0;i<4;i++)
        {
            int dirIdx = randomOrder[i];

            int new_row = parentTile.row + dirY[dirIdx];
            int new_col = parentTile.col + dirX[dirIdx];

            bool isTileOnBoard = new_col>0&&new_col<nodesPerRow&&new_row>0&&new_row<nodesPerRow;
            if(!isTileOnBoard)continue;

            int nbrIdx = convertCoordsToIndex(Vector2(new_col,new_row),nodesPerRow);
            int nbrRep = findDSU(nbrIdx,rep);
            if(nbrRep!=parentRep)
            {

                unionDSU(nbrRep,parentRep,rep);
                if(dirX[dirIdx]==2)
                {
                    Tile *nbrTile = &gridObj->grid[parentTile.row][parentTile.col+1];
                    if(nbrTile->state==TileState::notVisited)
                    {
                        nbrTile->state = TileState::wall;
                    }

                }
                else if(dirX[dirIdx]==-2)
                {
                    Tile *nbrTile = &gridObj->grid[parentTile.row][parentTile.col-1];
                    if(nbrTile->state==TileState::notVisited)
                    {
                        nbrTile->state = TileState::wall;
                    }
                }
                else if(dirY[dirIdx]==2)
                {
                    Tile *nbrTile = &gridObj->grid[parentTile.row+1][parentTile.col];
                    if(nbrTile->state==TileState::notVisited)
                    {
                        nbrTile->state = TileState::wall;
                    }
                }
                else if(dirY[dirIdx]==-2)
                {
                    Tile *nbrTile =  &gridObj->grid[parentTile.row-1][parentTile.col];
                    if(nbrTile->state==TileState::notVisited)
                    {
                        nbrTile->state = TileState::wall;
                    }
                }
                renderGrid(gridObj,window);
                std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
            }

        }
    }
    delete []rep;
}


void drawInitialTiles(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,std::vector<Vector2>*walls)
{
    for(int y = 2;y<gridObj->gridSize-2;y+=2)
        for(int x=2;x<gridObj->gridSize-2;x+=2)
        {
            if(gridObj->grid[y][x].state==TileState::notVisited)
            {
                gridObj->grid[y][x].state = TileState::wall;
            }

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
