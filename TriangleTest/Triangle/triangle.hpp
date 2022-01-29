#include <iostream>
using namespace std;

class Triangle
{
public:
    Triangle(int sideLength1, int sideLength2, int sideLength3);
    bool IsValidTriangle();
    std::string GetTringleTypeString();

private:
    enum class TriangleType
    {
        Invalid,
        Equilateral,
        Isoceles,
        Scalene
    };

    int mSideLength1 = 0;
    int mSideLength2 = 0;
    int mSideLength3 = 0;

    TriangleType triangleType = TriangleType::Invalid;

    void DetermineTriangleType();
};
