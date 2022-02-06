#include <list>
using namespace std;

class Statistic
{
public:
    Statistic();

    void add(double x);

    double average() const;

    double STD() const;

private:
    int numPoints = 0;
    double sum = 0;
    double summedSquares = 0;
    double calcSampleVarience() const;
};