#include "visualizePattern.h"
#include <vector>
#include <random>
#include <iostream>
#include "algorithm"
#include <queue>
#include "../Others/DSU.h"

struct EdgePrim{
    Vector2 from;
    Vector2 middle;
    Vector2 to;
    int value;
    EdgePrim(const Vector2& from, const Vector2& middle, const Vector2& to,int val)
        : from(from), middle(middle), to(to),value(val) {}
};
struct CompareEdges{
    bool operator()(const EdgePrim& edge1,const EdgePrim& edge2)const{
        return edge1.value>edge2.value;
    }
};


void addAdjancentEdges(int nodesPerRow ,std::priority_queue<EdgePrim,std::vector<EdgePrim>,CompareEdges> *edgesPQ,Vector2 currentTileCoords)
{
    int dirX[] = {0,0,2,-2};
    int dirY[] = {2,-2,0,0};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10000);

    for(int i=0;i<4;i++)
    {
        int new_row = currentTileCoords.row + dirY[i];
        int new_col = currentTileCoords.col + dirX[i];


        bool isTileOnBoard = new_col>0&&new_col<nodesPerRow&&new_row>0&&new_row<nodesPerRow;
        if(!isTileOnBoard)continue;

        Vector2 middle;
        Vector2 to(new_col,new_row);
        if(dirX[i]==2)
        {
            middle = Vector2(currentTileCoords.col+1,currentTileCoords.row);

        }
        else if(dirX[i]==-2)
        {
            middle= Vector2(currentTileCoords.col-1,currentTileCoords.row);
        }
        else if(dirY[i]==2)
        {
            middle= Vector2(currentTileCoords.col,currentTileCoords.row+1);
        }
        else if(dirY[i]==-2)
        {
                middle= Vector2(currentTileCoords.col,currentTileCoords.row-1);
        }
        int value = dis(gen);
        EdgePrim newEdge(currentTileCoords,middle,to,value);
        edgesPQ->push(newEdge);
    }
}


void applyPrimAlgorithm(Grid *gridObj,std::vector<Vector2>*walls)
{

    int nodesPerRow = gridObj->gridSize-2;
    int *rep = new int[nodesPerRow*nodesPerRow];
    for(int i=0;i<nodesPerRow*nodesPerRow;i++)
    {
        rep[i]= i;
    }


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, nodesPerRow-1);

    int startingTileCol = dis(gen);
    while(startingTileCol%2!=0)startingTileCol=dis(gen);

    int startingTileRow = dis(gen);
    while(startingTileRow%2!=0)startingTileRow=dis(gen);

    std::cout<<startingTileCol<<" "<<startingTileRow<<std::endl;

    Vector2 startingTileCoords(startingTileCol,startingTileRow);

    std::priority_queue<EdgePrim,std::vector<EdgePrim>,CompareEdges> edgesPQ;
    addAdjancentEdges(nodesPerRow,&edgesPQ,startingTileCoords);
    while(!edgesPQ.empty())
    {
        EdgePrim currentEdge = edgesPQ.top();
        edgesPQ.pop();

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
            addAdjancentEdges(nodesPerRow,&edgesPQ,currentEdge.to);
        }
    }
    delete [] rep;
}

void generatePrimMaze(Grid *gridObj,std::vector<Vector2>*walls)
{
    applyPrimAlgorithm(gridObj,walls);

    std::vector<Vector2> frame = generateFrame(gridObj);
    walls->insert(walls->begin(),frame.begin(),frame.end());
};
