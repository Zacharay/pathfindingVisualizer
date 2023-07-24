#include "getNeighbors.h"

const int dirX[] = {0,0,1,-1};
const int dirY[] = {1,-1,0,0};

bool isTileOnBoard(const Grid &gridObj,int row,int col)
{
    return col>=0&&col<gridObj.gridSize&&row>=0&&row<gridObj.gridSize;
}

void getNeighbors(Tile &currentTile,std::vector<Tile*>&neighbours,Grid &gridObj)
{
    for(int i=0;i<4;i++)
    {
        int nbrRow = currentTile.pos.row+dirY[i];
        int nbrCol = currentTile.pos.col+dirX[i];
        if(!isTileOnBoard(gridObj,nbrRow,nbrCol))continue;

        Tile* neighborTile = &gridObj.grid[nbrRow][nbrCol];
        if(neighborTile->state!=TileState::wall)
        {
            neighbours.push_back(neighborTile);
        }

    }
}
