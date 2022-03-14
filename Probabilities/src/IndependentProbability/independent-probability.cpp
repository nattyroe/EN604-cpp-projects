#include "independent-probability.hpp"

// Independent Probability object constructor; stores
// given probability.
IndependentProb::IndependentProb(double probability)
{
    if (probability >= 0.0 && probability <= 1.0)
    {
        this->probability = probability;
    }
    else
    {
        throw invalidProbEx;
    }
} // End constructor

// NOT operator for finding P(NOT A)
IndependentProb operator~(const IndependentProb &probA)
{
    return IndependentProb(1.0 - probA.getProbability());
}

// AND operator for finding P(A AND B)
IndependentProb operator&(const IndependentProb &probA, const IndependentProb &probB)
{
    return IndependentProb(probA.getProbability() * probB.getProbability());
}

// OR operator for finding P(A AND/OR B)
IndependentProb operator|(const IndependentProb &probA, const IndependentProb &probB)
{
    return IndependentProb(1.0 - ((~probA).getProbability() * (~probB).getProbability()));
}

// EXCLUSIVE OR operator for finding P(A XOR B)
IndependentProb operator^(const IndependentProb &probA, const IndependentProb &probB)
{
    return IndependentProb((probA | probB).getProbability() - (probA & probB).getProbability());
}

// EXCLUSIVE operator for finding P(A BUT NOT B)
IndependentProb operator-(const IndependentProb &probA, const IndependentProb &probB)
{
    return IndependentProb(probA.getProbability() * (~probB).getProbability());
}
