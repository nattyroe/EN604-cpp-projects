#include "Statistic/statistic.hpp"
#include <iostream>
#include <array>

using namespace std;

int main()
{
    Statistic *statCalc = new Statistic();

    array<double, 5> test = {1.0, 2.0, 3.0, 4.0, 5.0};
    for (int i = 0; i < test.size(); i++)
    {
        statCalc->add(test[i]);
    }

    cout << "Mean: " << statCalc->average() << endl;
    cout << "Std Deviation: " << statCalc->STD() << endl;
};