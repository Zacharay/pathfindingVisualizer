#include "DSU.h"
int convertCoordsToIndex(Vector2 coords,int nodesPerRow)
{
    return coords.col + coords.row*nodesPerRow;
}

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

