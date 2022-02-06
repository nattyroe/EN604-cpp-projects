#include <list>
using namespace std;

// Creates Statistic object that provides
// sample mean and sample standard deviations for
// provided distributions. Values are added to
// the distribution as floats one at a time.
class Statistic
{
public:
    // Uses Default empty constructor

    // Add given double to the distribution
    void add(double x);

    // Retrieve the average (sample mean) for the
    // current distribution
    double average() const;

    // Retrieve the sample standard deviation for
    // the current distribution
    double STD() const;

private:
    // Number of points added to the distribution
    int numPoints = 0;
    // Current total of all values in distribution
    double sum = 0;
    // Current sum of the squares of all values in distribution
    double summedSquares = 0;

    // Calculates and returns the current sample varience
    // for the distribution
    double calcSampleVarience() const;
};