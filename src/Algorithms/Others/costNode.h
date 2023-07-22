#pragma once
#include "../../Grid/Vector2.h"
#include <math.h>
enum NodeStatus{
    nodeNotVisited,
    inQueue,
    nodeVisited
};

struct costNode{
    Vector2 pos;
    int fCost;
    int gCost;
    int hCost;
    int nodeStatus;
    costNode(int row,int col):
    pos(col,row),fCost(0),gCost(1000),hCost(0),nodeStatus(0){}
    void calculateDistanceToDest(Vector2 destCoords)
    {
        int dist = std::abs(pos.col-destCoords.col)+std::abs(pos.row-destCoords.row);
        hCost = dist;
    }
};
