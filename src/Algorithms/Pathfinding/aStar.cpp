#include "visualizePathfinding.h"
#include "../Others/calculateDistance.h"
#include <iostream>
#include <queue>
#include <math.h>

struct Node{
    Vector2 pos;
    int fCost;
    int gCost=10000;
    int hCost;
    int nodeStatus = 0;
    void calculateDistanceToDest(Vector2 destCoords)
    {
        int dist = std::abs(pos.col-destCoords.col)+std::abs(pos.row-destCoords.row);
        hCost = dist;
    }
};

struct CompareNodes {
    bool operator()(const Node *nodeA, const Node *nodeB) const {
        return nodeA->fCost > nodeB->fCost;
    }
};

void astarAlgorithm(Grid *gridObj,std::vector<Vector2>*path,bool &pathFound)
{
    Node **nodes;
    nodes = new Node*[gridObj->gridSize];
    for(int i=0;i<gridObj->gridSize;i++)
    {
        nodes[i] = new Node[gridObj->gridSize];
    }
    for(int i=0;i<gridObj->gridSize;i++)
    {
        for(int j=0;j<gridObj->gridSize;j++)
        {
            nodes[i][j].pos = Vector2(j,i);
            nodes[i][j].calculateDistanceToDest(gridObj->destCoords);
            nodes[i][j].gCost = 1000;
        }
    }

    std::priority_queue<Node*,std::vector<Node*>,CompareNodes>nodesPQ;

    Node *srcNode = &nodes[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    srcNode->fCost = srcNode->hCost;
    srcNode->gCost = 0;
    nodesPQ.push(srcNode);

    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};
    while(!nodesPQ.empty())
    {
        Node *currentNode = nodesPQ.top();
        nodesPQ.pop();
        //std::cout<<"xd";

        currentNode->nodeStatus = 2;
        path->push_back(currentNode->pos);

        for(int i=0;i<4;i++)
        {
            int new_col = currentNode->pos.col+dirX[i];
            int new_row = currentNode->pos.row+dirY[i];
            Node *neighborNode = &nodes[new_row][new_col];

            if(gridObj->grid[new_row][new_col].state == TileState::destination)
            {
                gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[currentNode->pos.row][currentNode->pos.col];
                pathFound =true;
                for(int i=0;i<gridObj->gridSize;i++)
                {
                    delete [] nodes[i];
                }
                delete []nodes;
                return;
            }
            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
            if(!isTileOnBoard|| gridObj->grid[new_row][new_col].state == TileState::wall)continue;

            if(neighborNode->nodeStatus!=2)
            {

                int tentativeG = currentNode->gCost +1;
                if(tentativeG < neighborNode->gCost)
                {
                     neighborNode->gCost = tentativeG;
                     neighborNode->fCost =neighborNode->gCost  + neighborNode->hCost;
                     gridObj->grid[neighborNode->pos.row][neighborNode->pos.col].parentTile = &gridObj->grid[currentNode->pos.row][currentNode->pos.col];
                     if(neighborNode->nodeStatus!=1)
                     {
                        neighborNode->nodeStatus = 1;
                        nodesPQ.push(neighborNode);
                     }
                }
            }

        }

    }

    for(int i=0;i<gridObj->gridSize;i++)
    {
        delete [] nodes[i];
    }
    delete []nodes;
}
