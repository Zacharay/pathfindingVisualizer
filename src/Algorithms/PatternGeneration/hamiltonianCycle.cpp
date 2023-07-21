#include "visualizePattern.h"
#include <vector>
#include <random>
#include <iostream>
#include "algorithm"


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

void kruskalMst(Grid *gridObj,std::vector<Vector2>*walls)
{
    int nodesPerRow = gridObj->gridSize-2;
    int *rep = new int[nodesPerRow*nodesPerRow];
    for(int i=0;i<nodesPerRow*nodesPerRow;i++)
    {
        rep[i]= i;
    }


    std::vector<Vector2> wallsCopy;
    for(const Vector2& wall : *walls)
    {
        wallsCopy.push_back(wall);

    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(wallsCopy.begin(), wallsCopy.end(), gen);

    std::vector<int>randomOrder = {0,1,2,3};
    int dirX[] = {0,0,2,-2};
    int dirY[] = {2,-2,0,0};
    int t = 0;
    while(!wallsCopy.empty())
    {
        Vector2 parentTile = wallsCopy.back();
        wallsCopy.pop_back();

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
                    walls->push_back(Vector2(parentTile.col+1,parentTile.row));

                }
                else if(dirX[dirIdx]==-2)
                {
                    walls->push_back(Vector2(parentTile.col-1,parentTile.row));
                }
                else if(dirY[dirIdx]==2)
                {
                    walls->push_back(Vector2(parentTile.col,parentTile.row+1));
                }
                else if(dirY[dirIdx]==-2)
                {
                    walls->push_back(Vector2(parentTile.col,parentTile.row-1));
                }
            }

        }
    }
    delete []rep;
}


void generateInitialTiles(Grid *gridObj,std::vector<Vector2>*walls)
{
    for(int y = 2;y<gridObj->gridSize-2;y+=2)
        for(int x=2;x<gridObj->gridSize-2;x+=2)
        {
            walls->push_back(Vector2(x,y));
        }
}

void generateHamiltonian(Grid *gridObj,std::vector<Vector2>*walls)
{
    std::vector<Vector2> frame = generateFrame(gridObj);

    generateInitialTiles(gridObj,walls);

    kruskalMst(gridObj,walls);
    walls->insert(walls->begin(),frame.begin(),frame.end());
};
