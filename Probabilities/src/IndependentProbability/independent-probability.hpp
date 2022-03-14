#pragma once
#include <exception>
// @file
// @author Nathan Roe
// Object to represent an Independent Probabalistic Event
//
// Each IndependentProb stores an event probability created
// on construction, and can be accessed through getter.
// Event probabilities must be between 0.0 and 1.0, inclusive.
class IndependentProb
{
public:
    // Construct Probability Event with given probability.
    //
    // @param probability - likelyhood of event; must be
    //    between 0.0 and 1.0 inclusively, or will throw
    //    invalidProbability exception
    IndependentProb(double probability);

    // Get the probability of this event
    //
    // @return a double containing event probability
    double getProbability() const { return this->probability; };

    // Exception indicating an invalid probability
    // was provided.
    class invalidProbability : public std::exception
    {
    public:
        virtual const char *what() const throw()
        {
            return "Probability not between 0.0 and 1.0";
        }
    } invalidProbEx;

private:
    double probability = 0.0;
};

// NOT operator for finding P(NOT A)
IndependentProb operator~(const IndependentProb &probA);

// AND operator for finding P(A AND B)
IndependentProb operator&(const IndependentProb &probA,
                          const IndependentProb &probB);

// OR operator for finding P(A AND/OR B)
IndependentProb operator|(const IndependentProb &probA,
                          const IndependentProb &probB);

// EXCLUSIVE OR operator for finding P(A XOR B)
IndependentProb operator^(const IndependentProb &probA,
                          const IndependentProb &probB);

// EXCLUSIVE operator for finding P(A BUT NOT B)
IndependentProb operator-(const IndependentProb &probA,
                          const IndependentProb &probB);