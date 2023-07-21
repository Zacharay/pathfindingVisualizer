#include "visualizePattern.h"
#include <vector>

void spiralOneIteration(int gridSize,std::vector<Vector2>*spiralPoints,int offset)
{
    //bottom row
    for(int i=gridSize-1;i>=offset;i--)
    {
        int row = gridSize-1;
        int col = i;
        spiralPoints->push_back(Vector2(col,row));
    }
    //left col
    for(int i=gridSize-1;i>=offset;i--)
    {
        int row = i;
        int col = offset;
        spiralPoints->push_back(Vector2(col,row));
    }
    //top row
    for(int i=offset;i<gridSize;i++)
    {
        int row = offset;
        int col = i;
        spiralPoints->push_back(Vector2(col,row));
    }
    //right col
    for(int i=offset;i<gridSize-2;i++)
    {
        int row =i;
        int col = gridSize-1;
        spiralPoints->push_back(Vector2(col,row));
    }
    Vector2 lastElement = spiralPoints->back();

    Vector2 dirElement(lastElement.col-1,lastElement.row);
    spiralPoints->push_back(dirElement);
}

void generateSpiral(bool isInnerSpiral,Grid *gridObj,std::vector<Vector2>*walls)
{
    int i=0;
    while(i*2<gridObj->gridSize)
    {
        spiralOneIteration(gridObj->gridSize-i,walls,i);
        i+=2;
    }
    walls->pop_back();

    if(isInnerSpiral)std::reverse(walls->begin(),walls->end());
}



