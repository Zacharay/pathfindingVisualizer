#include "calculateDistance.h"
#include "math.h"
int calculateDistance(Vector2 a,Vector2 b)
{
    return std::abs(a.col-b.col)+std::abs(a.row-b.row);
}
