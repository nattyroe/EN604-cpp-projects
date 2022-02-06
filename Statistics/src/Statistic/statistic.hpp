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
    int mNumPoints = 0;
    double mMean = 0;
    double mVariance = 0;
    list<double> mValues = {};
    void recalculateStats(double x);
};