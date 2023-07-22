#include "visualizePathfinding.h"
#include <queue>
#include "../Others/costNode.h"


struct CompareNodes {
    bool operator()(const costNode *nodeA, const costNode *nodeB) const {
        return nodeA->fCost > nodeB->fCost;
    }
};

void astarAlgorithm(Grid *gridObj,std::vector<Vector2>*path,bool &pathFound)
{
    std::vector<std::vector<costNode>>nodes(gridObj->gridSize,std::vector<costNode>(gridObj->gridSize,costNode(0,0)));


    for(int row=0;row<gridObj->gridSize;row++)
    {
        for(int col=0;col<gridObj->gridSize;col++)
        {
            nodes[row][col]= costNode(row,col);
            nodes[row][col].calculateDistanceToDest(gridObj->destCoords);
        }
    }

    std::priority_queue<costNode*,std::vector<costNode*>,CompareNodes>nodesPQ;

    costNode *srcNode = &nodes[gridObj->sourceCoords.row][gridObj->sourceCoords.col];
    srcNode->fCost = srcNode->hCost;
    srcNode->gCost = 0;
    nodesPQ.push(srcNode);

    int dirX[] = {0,0,1,-1};
    int dirY[] = {1,-1,0,0};
    while(!nodesPQ.empty())
    {
        costNode *currentNode = nodesPQ.top();
        nodesPQ.pop();
        currentNode->nodeStatus = NodeStatus::nodeVisited;
        path->push_back(currentNode->pos);

        for(int i=0;i<4;i++)
        {
            int new_col = currentNode->pos.col+dirX[i];
            int new_row = currentNode->pos.row+dirY[i];

            bool isTileOnBoard = new_col>=0&&new_col<gridObj->gridSize&&new_row>=0&&new_row<gridObj->gridSize;
            if(!isTileOnBoard|| gridObj->grid[new_row][new_col].state == TileState::wall)continue;

            costNode *neighborNode = &nodes[new_row][new_col];

            if(gridObj->grid[new_row][new_col].state == TileState::destination)
            {
                gridObj->grid[new_row][new_col].parentTile = &gridObj->grid[currentNode->pos.row][currentNode->pos.col];
                pathFound =true;
                return;
            }

            if(neighborNode->nodeStatus!=NodeStatus::nodeVisited)
            {

                int tentativeG = currentNode->gCost +1;
                if(tentativeG < neighborNode->gCost)
                {
                     neighborNode->gCost = tentativeG;
                     neighborNode->fCost =neighborNode->gCost  + neighborNode->hCost;
                     gridObj->grid[neighborNode->pos.row][neighborNode->pos.col].parentTile = &gridObj->grid[currentNode->pos.row][currentNode->pos.col];
                     if(neighborNode->nodeStatus!= NodeStatus::inQueue)
                     {
                        neighborNode->nodeStatus = NodeStatus::inQueue;
                        nodesPQ.push(neighborNode);
                     }
                }
            }

        }

    }
}
