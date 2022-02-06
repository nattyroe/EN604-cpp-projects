// Accepts command line args for double values
// (ints promoted to doubles) and calculates the
// sample mean and sample standard deviation for
// the given distribution

#include "Statistic/statistic.hpp"
#include <iostream>
#include <string>

using namespace std;

// Function main begins statistic evaluation loop
int main(int argc, char *argv[])
{
    Statistic *statCalc = new Statistic();

    // Iterate over command line args
    for (int i = 1; i < argc; i++)
    {
        // Add numbers to distribution
        try
        {
            double x = stod(argv[i]);
            statCalc->add(x);
        }
        // Catch inputs that can't be converted to numbers
        catch (const std::invalid_argument &e)
        {
            cout << "Could not interpret <" << argv[i] << "> as a double." << endl;
            cout << "Please update inputs to only include doubles." << endl;
            return 1;
        }
    }

    // Print out statistical info
    cout << "Mean: " << statCalc->average() << endl;
    cout << "Std Deviation: " << statCalc->STD() << endl;
    return 0;
} // End function main