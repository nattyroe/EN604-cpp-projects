#include "Statistic/statistic.hpp"
#include <iostream>
#include <array>

using namespace std;

int main()
{
    Statistic *statCalc = new Statistic();

    //array<double, 5> test = {1.0, 2.0, 3.0, 4.0, 5.0};
    array<double, 8> test = {10.0, 12.0, 23.0, 23.0, 16.0, 23.0, 21.0, 16.0};
    for (double x : test)
    {
        cout << "value: " << x << endl;
        statCalc->add(x);
    }

    cout << "Mean: " << statCalc->average() << endl;
    cout << "Std Deviation: " << statCalc->STD() << endl;
};