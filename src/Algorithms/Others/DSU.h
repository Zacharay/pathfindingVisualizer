#pragma once
#include "../../Grid/Vector2.h"
int convertCoordsToIndex(Vector2 coords,int nodesPerRow);
int findDSU(int a,int *rep);
void unionDSU(int a,int b, int *rep);
