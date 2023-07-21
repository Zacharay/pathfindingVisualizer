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

void generateOuterSpiral(Grid *gridObj,std::vector<Vector2>*spiralPoints)
{
    int i=0;
    while(i*2<gridObj->gridSize)
    {
        spiralOneIteration(gridObj->gridSize-i,spiralPoints,i);
        i+=2;
    }
    spiralPoints->pop_back();

}

void visualizeSpiral(Grid *gridObj,sf::RenderWindow *window,CONFIG *config,bool spiralInner)
{
    std::vector<Vector2>spiralPoints;
    generateOuterSpiral(gridObj,&spiralPoints);
    if(spiralInner)std::reverse(spiralPoints.begin(),spiralPoints.end());
    for(int i=0;i<spiralPoints.size();i++)
    {
        Vector2 coords = spiralPoints[i];
        gridObj->grid[coords.row][coords.col].state = TileState::wall;
        if(i%3==0)
        {
            renderGrid(gridObj,window);
            std::this_thread::sleep_for(std::chrono::milliseconds(101-config->visualizationSpeed));
        }
    }
    renderGrid(gridObj,window);
}

