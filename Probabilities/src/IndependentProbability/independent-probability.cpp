#include "independent-probability.hpp"

IndependentProbability::IndependentProbability(double probability)
{
    if (probability >= 0.0 && probability <= 1.0)
    {
        this->probability = probability;
    }
    else
    {
        throw invalidProbEx;
    }
}

double operator~(const IndependentProbability &probA)
{
    return 1.0 - probA.getProbability();
}

double operator&(const IndependentProbability &probA, const IndependentProbability &probB)
{
    return probA.getProbability() * probB.getProbability();
}

double operator|(const IndependentProbability &probA, const IndependentProbability &probB)
{
    return 1.0 - (~probA * ~probB);
}

double operator^(const IndependentProbability &probA, const IndependentProbability &probB)
{
    return (probA | probB) - (probA & probB);
}

double operator-(const IndependentProbability &probA, const IndependentProbability &probB)
{
    return probA.getProbability() * ~probB;
}
