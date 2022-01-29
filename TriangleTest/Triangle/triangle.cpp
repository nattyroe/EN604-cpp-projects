#include "triangle.h"

Triangle::Triangle(int sideLength1,
                   int sideLength2,
                   int sideLength3)
{
    mSideLength1 = sideLength1;
    mSideLength2 = sideLength2;
    mSideLength3 = sideLength3;
}

bool Triangle::IsValidTriangle()
{
    return true;
}
