// Accepts command line args for two double values
// (ints promoted to doubles) and calculates some
// probabilities based in the inputs

#include "IndependentProbability/independent-probability.hpp"
#include <iostream>

using namespace std;

// Function main begins statistic evaluation loop
int main(int argc, char *argv[])
{
    if (!(argc == 3))
    {
        cout << "Please provide two input values between 0.0 and 1.0." << endl;
        return EXIT_FAILURE;
    }
    else
    {
        IndependentProbability *a;
        IndependentProbability *b;

        // Add numbers to distribution
        try
        {
            double x = stod(argv[1]);
            a = new IndependentProbability(x);
            cout << "P(A) = " << a->getProbability() << endl;
        }
        // Catch inputs that can't be converted to numbers
        catch (const invalid_argument &e)
        {
            cout << e.what() << ": Could not interpret <" << argv[1] << "> as a double." << endl;
            return EXIT_FAILURE;
        }
        catch (const IndependentProbability::invalidProbability &e)
        {
            cout << e.what() << ": " << argv[1] << endl;
            return EXIT_FAILURE;
        }
        // Add numbers to distribution
        try
        {
            double y = stod(argv[2]);
            b = new IndependentProbability(y);
            cout << "P(B) = " << b->getProbability() << endl;
        }
        // Catch inputs that can't be converted to numbers
        catch (const invalid_argument &e)
        {
            cout << e.what() << ": Could not interpret <" << argv[2] << "> as a double." << endl;
            return EXIT_FAILURE;
        }
        catch (const IndependentProbability::invalidProbability &e)
        {
            cout << e.what() << ": " << argv[2] << endl;
            return EXIT_FAILURE;
        }

        cout << "P(~A) = " << ~*a << endl;
        cout << "P(~B) = " << ~*b << endl;
        cout << "P(A & B) = " << (*a & *b) << endl;
        cout << "P(A | B) = " << (*a | *b) << endl;
        cout << "P(A ^ B) = " << (*a ^ *b) << endl;
        cout << "P(A - B) = " << (*a - *b) << endl;
        cout << "P(B - A) = " << (*b - *a) << endl;
    }
    return EXIT_SUCCESS;
} // End function main