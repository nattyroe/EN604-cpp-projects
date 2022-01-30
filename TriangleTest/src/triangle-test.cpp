// Accepts user input for integer Triangle side lengths
// and returns the side-type of the given triangle

#include "Triangle/triangle.hpp"
#include <iostream>

using namespace std;

// Function main begins triangle evaluation loop
int main()
{
    // User input variable declarations
    int sideLength1;
    int sideLength2;
    int sideLength3;

    // Print to screen and store user input values
    cout << "Triangle Side Type Calculator" << endl;
    cout << "Enter First Side Length as an Integer:" << endl;
    cin >> sideLength1;

    if (!cin.fail())
    {
        cout << "Enter Second Side Length as an Integer:" << endl;
        cin >> sideLength2;
    }

    if (!cin.fail())
    {
        cout << "Enter Third Side Length as an Integer:" << endl;
        cin >> sideLength3;
    }

    // Return error if given value is not an integer
    if (cin.fail())
    {
        cout << "Side Lengths must be Integers" << endl;
        return 1;
    }

    // Create Triangle
    Triangle *triangle = new Triangle(sideLength1,
                                      sideLength2,
                                      sideLength3);
    // Determine if Triangle is valid
    if (triangle->IsValidTriangle())
    {
        // If triangle is valid, determing side-type
        cout << "This is a(n) <" + triangle->GetTriangleTypeString() + "> Triangle" << endl;
        return 0;
    }

    // If triangle is invalid, print error to console
    cout << "This is not a valid triangle" << endl;
    return 1;
} // End function main
