#include "generateFrame.h"
std::vector<Vector2> generateFrame(Grid *gridObj)
{
    std::vector<Vector2>frame;
    for(int i=0;i<gridObj->gridSize;i++)
    {
            frame.push_back(Vector2(i,0));
            frame.push_back(Vector2(0,i));
            frame.push_back(Vector2(gridObj->gridSize-1-i,gridObj->gridSize-1));
            frame.push_back(Vector2(gridObj->gridSize-1,gridObj->gridSize-1-i));
    }
    return frame;

}
