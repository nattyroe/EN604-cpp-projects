// @file
// @author Nathan Roe
//
// Accepts command line args for two double values
// (ints promoted to doubles) and calculates some
// probabilities based in the inputs. Alternately
// runs unit tests for the IndependentProb class

#include "IndependentProbability/independent-probability.hpp"
#include <iostream>

using namespace std;

// Run all probability operator calcs for given events A and B
void runProbabilities(const IndependentProb *a, const IndependentProb *b)
{
    // Run Probability Calcs
    cout << "P(~A) = " << (~*a).getProbability() << endl;
    cout << "P(~B) = " << (~*b).getProbability() << endl;
    cout << "P(A & B) = " << (*a & *b).getProbability() << endl;
    cout << "P(A | B) = " << (*a | *b).getProbability() << endl;
    cout << "P(A ^ B) = " << (*a ^ *b).getProbability() << endl;
    cout << "P(A - B) = " << (*a - *b).getProbability() << endl;
    cout << "P(B - A) = " << (*b - *a).getProbability() << endl;
}

// Function main begins probability evaluation loop
int main(int argc, char *argv[])
{
    // If Input args provided, run calcs on args
    if (argc == 3)
    {
        IndependentProb *a;
        IndependentProb *b;

        // Create IndependentProbability
        try
        {
            double x = stod(argv[1]);
            a = new IndependentProb(x);
            cout << "P(A) = " << a->getProbability() << endl;
        }
        // Catch inputs that can't be converted to numbers
        catch (const invalid_argument &e)
        {
            cout << e.what() << ": Could not interpret <" << argv[1] << "> as a double." << endl;
            return EXIT_FAILURE;
        }
        // Catch invalid probabilities
        catch (const IndependentProb::invalidProbability &e)
        {
            cout << e.what() << ": " << argv[1] << endl;
            return EXIT_FAILURE;
        }

        // Create IndependentProbability
        try
        {
            double y = stod(argv[2]);
            b = new IndependentProb(y);
            cout << "P(B) = " << b->getProbability() << endl;
        }
        // Catch inputs that can't be converted to numbers
        catch (const invalid_argument &e)
        {
            cout << e.what() << ": Could not interpret <" << argv[2] << "> as a double." << endl;
            return EXIT_FAILURE;
        }
        // Catch invalid probabilities
        catch (const IndependentProb::invalidProbability &e)
        {
            cout << e.what() << ": " << argv[2] << endl;
            return EXIT_FAILURE;
        }
        runProbabilities(a, b);
    }
    // If args are not provided, run default cases
    else
    {
        cout << "Running Probability Tests\n" << endl;

        int numTests = 8;
        double probabilities[numTests][2] = {{0, 1},
                                             {1, 0},
                                             {0.25, 0.75},
                                             {0.5, 0.5},
                                             {0, 0},
                                             {1, 1},
                                             {1.1, 0.2},
                                             {0.2, 1.1}};

        // Run each of the probability tests
        for (int idx = 0; idx < numTests; ++idx)
        {
            try
            {
                IndependentProb *a = new IndependentProb(probabilities[idx][0]);
                IndependentProb *b = new IndependentProb(probabilities[idx][1]);
                cout << "P(A) = " << a->getProbability() << endl;
                cout << "P(B) = " << b->getProbability() << endl;
                runProbabilities(a, b);
                cout << "\n" << endl;
            }
            catch (const IndependentProb::invalidProbability &e)
            {
                cout << e.what() << ": " << probabilities[idx][0]
                     << "  " << probabilities[idx][1] << "\n" << endl;
            }
        }
    }
    return EXIT_SUCCESS;
} // End function main