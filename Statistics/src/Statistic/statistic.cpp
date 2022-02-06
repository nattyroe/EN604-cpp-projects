#include "statistic.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Statistic::Statistic()
{
}

double Statistic::average() const
{
    return this->mMean;
}

double Statistic::STD() const
{
    return sqrt(this->mVariance);
}

void Statistic::add(double x)
{
    cout << "Adding " << x << endl;
    this->mValues.push_back(x);
    this->recalculateStats(x);
    cout << mNumPoints << endl;
}

void Statistic::recalculateStats(double x)
{
    ++mNumPoints;

    mMean += (x - mMean) / mNumPoints;
    cout << mMean << endl;

    double summedSquares = 0;
    for (double x : this->mValues)
    {
        summedSquares += pow(x - mMean, 2.0);
    }
    this->mVariance = summedSquares / mNumPoints;
}
