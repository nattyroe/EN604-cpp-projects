#include <exception>

class IndependentProbability
{
public:
    IndependentProbability(double probability);

    double getProbability() const { return this->probability; };

    class invalidProbability : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Probability not between 0.0 and 1.0";
        }
    } invalidprobex;

private:
    double probability = 0.0;
};

double operator~(const IndependentProbability &probA);
double operator&(const IndependentProbability &probA, const IndependentProbability &probB);
double operator|(const IndependentProbability &probA, const IndependentProbability &probB);
double operator^(const IndependentProbability &probA, const IndependentProbability &probB);
double operator-(const IndependentProbability &probA, const IndependentProbability &probB);