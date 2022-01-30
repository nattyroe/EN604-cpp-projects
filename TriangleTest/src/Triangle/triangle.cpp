#include "triangle.hpp"

// Triangle constructor; stores side lengths
// and determines triangle type
Triangle::Triangle(int sideLength1,
                   int sideLength2,
                   int sideLength3)
{
    mSideLength1 = sideLength1;
    mSideLength2 = sideLength2;
    mSideLength3 = sideLength3;

    this->DetermineTriangleType();
} // End constructor

// Function to determine side type based on
// comparing triangle side lengths
void Triangle::DetermineTriangleType()
{
    // Equilateral if all sides are equal
    if (mSideLength1 == mSideLength2 && mSideLength2 == mSideLength3)
    {
        this->triangleType = TriangleType::Equilateral;
    }
    // Isoceles if only two sides are equal
    else if (mSideLength1 == mSideLength2 || mSideLength2 == mSideLength3 || mSideLength1 == mSideLength3)
    {
        this->triangleType = TriangleType::Isoceles;
    }
    // Scalene if no sides are equal
    else if (this->IsValidTriangle())
    {
        this->triangleType = TriangleType::Scalene;
    }
    // Invalid, if the sides cannot form a triangle
    else
    {
        this->triangleType = TriangleType::Invalid;
    }
} // End function DetermineTriangleType

// Function determines whether a valid triangle can be formed
// with the given side lengths, based on the Triangle
// Inequality Theorem: https://en.wikipedia.org/wiki/Triangle_inequality
bool Triangle::IsValidTriangle()
{
    if (mSideLength1 + mSideLength2 <= mSideLength3 ||
        mSideLength2 + mSideLength3 <= mSideLength1 ||
        mSideLength1 + mSideLength3 <= mSideLength2)
    {
        return false;
    }
    else
    {
        return true;
    }
} // End function IsValidTriangle

// Function returns string containing triangle side type
std::string Triangle::GetTriangleTypeString()
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
} // End function GetTriangleTypeString
