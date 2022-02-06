#include "statistic.hpp"
#include <iostream>
#include <cmath>

using namespace std;

// Function to calculate and retrieve the average
// (sample mean) of the current distribution
double Statistic::average() const
{
    // Calculate average of values added
    if (this->numPoints > 0)
    {
        // Integer numPoints promoted to double
        return this->sum / this->numPoints;
    }
    // Avoid divide by 0 error
    else
    {
        return 0;
    }
} // End function average

// Function to calculate and retrieve the sample
// standard deviation of the current distribution
double Statistic::STD() const
{
    return sqrt(calcSampleVarience());
} // End function STD

// Function to add new value to the distribution.
void Statistic::add(double x)
{
    // Update data point count
    ++this->numPoints;

    // Update sums required for tracking the
    // running mean/standard dev
    this->sum += x;
    this->summedSquares += x * x;
} // End function add

// Function to calculate the sample varience of
// the current distribution
double Statistic::calcSampleVarience() const
{
    // Var = [Σx^2 * (Σx*Σx/n)] / (n-1)
    if (this->numPoints > 1)
    {
        // Integer numPoints is promoted to double
        double squaredSum = this->sum * this->sum / this->numPoints;
        return (this->summedSquares - squaredSum) / (this->numPoints - 1);
    }
    // Avoid divide by 0 error
    else
    {
        return 0;
    }
} // End function calcSampleVarience