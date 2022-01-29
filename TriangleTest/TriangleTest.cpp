#include "Triangle/triangle.hpp"
#include <iostream>

using namespace std;

int main()
{
    int sideLength1;
    int sideLength2;
    int sideLength3;

    cout << "Triangle Calculator" << endl;
    cout << "Enter First Side Length:" << endl;
    cin >> sideLength1;

    cout << "Enter Second Side Length:" << endl;
    cin >> sideLength2;

    cout << "Enter Third Side Length:" << endl;
    cin >> sideLength3;

    Triangle *triangle = new Triangle(sideLength1,
                                      sideLength2,
                                      sideLength3);
    if (triangle->IsValidTriangle())
    {
        cout << "This is a(n) <" + triangle->GetTringleTypeString() + "> Triangle" << endl;
        return 0;
    }

    cout << "This is not a valid triangle" << endl;
    return 1;
}
