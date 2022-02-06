#include "statistic.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Statistic::Statistic()
{
}

double Statistic::average() const
{
    return this->sum / this->numPoints;
}

double Statistic::STD() const
{
    return sqrt(calcSampleVarience());
}

void Statistic::add(double x)
{
    ++this->numPoints;

    this->sum += x;
    this->summedSquares += x * x;
}

double Statistic::calcSampleVarience() const
{
    if (numPoints > 1)
    {
        // Integer numPoints is promoted to double
        double squaredSum = this->sum * this->sum / this->numPoints;
        return (this->summedSquares - squaredSum) / (this->numPoints - 1);
    }
    else
    {
        return 0;
    }
}