#include "generateFrame.h"
void generateFrame(Grid *gridObj,std::vector<Vector2> *walls)
{

    for(int i=0;i<gridObj->gridSize;i++)
    {
            walls->push_back(Vector2(i,0));
            walls->push_back(Vector2(0,i));
            walls->push_back(Vector2(gridObj->gridSize-1-i,gridObj->gridSize-1));
            walls->push_back(Vector2(gridObj->gridSize-1,gridObj->gridSize-1-i));
            gridObj->grid[0][i].state = TileState::wall;
    }

}
