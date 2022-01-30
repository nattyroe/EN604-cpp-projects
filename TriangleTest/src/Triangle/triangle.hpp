#include <iostream>
using namespace std;

// Creates Triangle object with three sides as provided
// to the contstructor. Upon instantiation, the Triangle
// determines its side-type, and the user can retrieve
// a string of the type, and whether the triangle is valid.
class Triangle
{
public:
    // Object constructor, with integer side lengths
    // as inputs
    Triangle(int sideLength1, int sideLength2, int sideLength3);

    // Evaluate triangle side lengths to determine
    // whether it is a valid shape
    bool IsValidTriangle();

    // Returns a string contatining the side-type
    // of this Triangle in Title Case
    std::string GetTriangleTypeString();

private:
    // Enum of possible triangle side types
    enum class TriangleType
    {
        Invalid,
        Equilateral,
        Isoceles,
        Scalene
    };

    // Triangle side lengths
    int mSideLength1 = 0;
    int mSideLength2 = 0;
    int mSideLength3 = 0;

    TriangleType triangleType = TriangleType::Invalid;

    // Evaluates side lengths to determine
    // the side type of the triangle
    void DetermineTriangleType();
};
