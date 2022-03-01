#include "independent-probability.hpp"

IndependentProbability::IndependentProbability(double probability)
{
    if (probability >= 0.0 && probability <= 1.0)
    {
        this->probability = probability;
    }
    else
    {
        throw invalidprobex;
    }
}
