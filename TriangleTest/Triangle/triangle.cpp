#include "triangle.hpp"

Triangle::Triangle(int sideLength1,
                   int sideLength2,
                   int sideLength3)
{
    mSideLength1 = sideLength1;
    mSideLength2 = sideLength2;
    mSideLength3 = sideLength3;

    this->DetermineTriangleType();
}

void Triangle::DetermineTriangleType()
{
    if (mSideLength1 == mSideLength2 && mSideLength2 == mSideLength3)
    {
        this->triangleType = TriangleType::Equilateral;
    }
    else if (mSideLength1 == mSideLength2 || mSideLength2 == mSideLength3 || mSideLength1 == mSideLength3)
    {
        this->triangleType = TriangleType::Isoceles;
    }
    else if (this->IsValidTriangle())
    {
        this->triangleType = TriangleType::Scalene;
    }
    else
    {
        this->triangleType = TriangleType::Invalid;
    }
}

bool Triangle::IsValidTriangle()
{
    if (mSideLength1 + mSideLength2 <= mSideLength3)
    {
        return false;
    }
    else if (mSideLength2 + mSideLength3 <= mSideLength1)
    {
        return false;
    }
    else if (mSideLength1 + mSideLength3 <= mSideLength2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::string Triangle::GetTringleTypeString()
{
    switch (this->triangleType)
    {
    case TriangleType::Equilateral:
        return "Equilateral";
    case TriangleType::Isoceles:
        return "Isoceles";
    case TriangleType::Scalene:
        return "Scalene";
    default:
        return "Invalid";
    }
}
