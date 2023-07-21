#include "visualizePattern.h"
#include <vector>
#include <random>
#include <iostream>
#include "algorithm"

struct Edge{
    Vector2 from;
    Vector2 middle;
    Vector2 to;
    Edge(const Vector2& from, const Vector2& middle, const Vector2& to)
        : from(from), middle(middle), to(to) {}
};

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
std::vector<Vector2> generateInitialTiles(Grid *gridObj)
{
    std::vector<Vector2>initialTiles;
    for(int y = 2;y<gridObj->gridSize-2;y+=2)
        for(int x=2;x<gridObj->gridSize-2;x+=2)
        {
           initialTiles.push_back(Vector2(x,y));
        }
    return initialTiles;
}

void generateAllEdges(Grid *gridObj,std::vector<Edge>*edges)
{
    std::vector<Vector2>initialTiles = generateInitialTiles(gridObj);
    int nodesPerRow = gridObj->gridSize-2;
    int dirX[] = {0,0,2,-2};
    int dirY[] = {2,-2,0,0};
    for(int i=0;i<initialTiles.size();i++)
    {
        Vector2 from = initialTiles[i];
        for(int j=0;j<4;j++)
        {
            int new_row = initialTiles[i].row + dirY[j];
            int new_col = initialTiles[i].col + dirX[j];


            bool isTileOnBoard = new_col>0&&new_col<nodesPerRow&&new_row>0&&new_row<nodesPerRow;
            if(!isTileOnBoard)continue;

            Vector2 middle;
            Vector2 to(new_col,new_row);
            if(dirX[j]==2)
            {
                middle = Vector2(initialTiles[i].col+1,initialTiles[i].row);

            }
            else if(dirX[j]==-2)
            {
                middle= Vector2(initialTiles[i].col-1,initialTiles[i].row);
            }
            else if(dirY[j]==2)
            {
                middle= Vector2(initialTiles[i].col,initialTiles[i].row+1);
            }
            else if(dirY[j]==-2)
            {
                middle= Vector2(initialTiles[i].col,initialTiles[i].row-1);
            }
            Edge newEdge(from,middle,to);
            edges->push_back(newEdge);
        }
    }

}


void applyKruskalAlgorithm(Grid *gridObj,std::vector<Vector2>*walls)
{
    int nodesPerRow = gridObj->gridSize-2;
    int *rep = new int[nodesPerRow*nodesPerRow];
    for(int i=0;i<nodesPerRow*nodesPerRow;i++)
    {
        rep[i]= i;
    }


    std::vector<Edge>edges;
    generateAllEdges(gridObj,&edges);



    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(edges.begin(), edges.end(), gen);

    while(!edges.empty())
    {
        Edge currentEdge = edges.back();
        edges.pop_back();

        int fromIdx = convertCoordsToIndex(currentEdge.from,nodesPerRow);
        int fromRep = findDSU(fromIdx,rep);
        int toIdx = convertCoordsToIndex(currentEdge.to,nodesPerRow);
        int toRep = findDSU(toIdx,rep);

        if(toRep!=fromRep)
        {
            unionDSU(fromRep,toRep,rep);
            walls->push_back(currentEdge.from);
            walls->push_back(currentEdge.middle);
            walls->push_back(currentEdge.to);
        }
    }
    delete []rep;
}

void generateKruskalMaze(Grid *gridObj,std::vector<Vector2>*walls)
{
    applyKruskalAlgorithm(gridObj,walls);

    std::vector<Vector2> frame = generateFrame(gridObj);
    walls->insert(walls->begin(),frame.begin(),frame.end());
};
